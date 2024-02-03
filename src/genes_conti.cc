
#include "genes_conti.h"
#include <cstdlib>
#include <cstdio>
#include <Rcpp.h>
#include <random>
#include <algorithm>

genes_conti::genes_conti( go_graph_conti &graph, istream &annotation, istream &data ) 
{
	// annotation = gene | GO1 | GO2 | GO3 ...
	// go through annotation file, and add genes to all annotated GOs and their parents 
	string line ;
	while ( annotation ) {
		getline( annotation, line ) ;
		istringstream is( line.c_str() ) ;
		string gene_name ;
		is >> gene_name ;

		if ( gene_name != "" ) {
			set<go_obj_conti*> parents ;
			string go_name ;
			while ( is >> go_name ) {
				graph.get_parents( go_name, &parents ) ;
			}
			if ( parents.size() > 0 ) {
				//Rcpp::Rcout << "gene name: " << gene_name << ", parents.size: " << parents.size() << endl;
				genemap[gene_name] = new gene_conti( gene_name, parents ) ;
			} else {
				Rcpp::Rcerr << gene_name << " not mapped.\n" ;
			}
		}
	}
	//Rcpp::Rcout << "Annotated " << genemap.size() << " genes." << endl ;
	
	while( data ) {
		getline( data, line ) ;
		istringstream is( line.c_str() ) ;
		string gene_name ;
		is >> gene_name ;

		if ( genemap.find( gene_name ) != genemap.end() ) {
		
			double ch_s ;
			is >> ch_s ;  // substituion chimp->human synonymous

			double ch_ns ;
			is >> ch_ns ;  // substituion chimp->human non-synonymous

			double hh_s ;
			is >> hh_s ; // human variable synonymous

			double hh_ns ;
			is >> hh_ns ; // human variable non-synonymous

			genemap[gene_name]->add( static_cast<int>(ch_s),
			 			static_cast<int>(ch_ns), 
						static_cast<int>(hh_s),
					 	static_cast<int>(hh_ns) ) ;
			genevec.push_back( genemap[gene_name] ) ;
		}
	}
}

genes_conti::~genes_conti(  ) 
{
	for ( map<string, gene_conti*>::iterator it = genemap.begin() ; 
								it != genemap.end() ; ++it )  
		delete it->second ;
}

void genes_conti::create_random_set(  ) 
{
      	std::mt19937 g(R::runif(0, 1e+05));
        std::shuffle( genevec.begin(), genevec.end(), g ) ;

        int i = 0 ;

        for ( map<string,gene_conti*>::const_iterator it = genemap.begin() ;
                        it != genemap.end() ; ++it )
        {
                it->second->write_data_gos( genevec[i]->get_gos() ) ;
                i++ ;
        }
}

