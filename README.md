### GOfuncR: Gene Ontology Enrichment Using FUNC 

_GOfuncR_ performs a gene ontology enrichment analysis based on the ontology enrichment software [_FUNC_](https://www.ncbi.nlm.nih.gov/pmc/articles/PMC1800870/).
It provides the standard candidate vs. background enrichment analysis using the hypergeometric test, as well as three additional tests: (i) the Wilcoxon rank-sum test that is used when genes are ranked, (ii) a binomial test that can be used when genes are associated with two counts, e.g. amino acid changes since a common ancestor in two different species, and (iii) a Chi-square or Fisher's exact test that is used in cases when genes are associated with four counts, e.g. non-synonymous or synonymous variants that are fixed between or variable within species.  

To correct for multiple testing and interdependency of the tests, family-wise error rates (FWER) are computed based on random permutations of the gene-associated variables.
_GOfuncR_ also provides tools for exploring the ontology graph and the annotations, and options to take gene-length or spatial clustering of genes into account during testing.  

GO-annotations and gene-coordinates are obtained from _OrganismDb_ packages ([_Homo.sapiens_](https://www.bioconductor.org/packages/release/data/annotation/html/Homo.sapiens.html) by default) or _OrgDb_ and _TxDb_ packages.
The gene ontology graph (obtained from [geneontology](http://current.geneontology.org/ontology/), release 01-May-2021), is integrated in the package.
It is also possible to provide custom gene coordinates, annotations and ontologies.


#### Installation

A stable release version can be obtained from [_Bioconductor_](https://www.bioconductor.org/packages/release/bioc/html/GOfuncR.html).


+ Installation from Bioconductor

```r
if (!requireNamespace("BiocManager", quietly=TRUE))
    install.packages("BiocManager")
BiocManager::install("GOfuncR")
```

The developmental (this) version can be obtained from the ['devel' version of Bioconductor](https://bioconductor.org/developers/how-to/useDevel/) or directly from
GitHub:


+ Installation from GitHub

```r
if (!requireNamespace("devtools", quietly=TRUE))
    install.packages("devtools")
devtools::install_github("sgrote/GOfuncR")
```


#### Usage

See the [vignette](https://bioconductor.org/packages/devel/bioc/vignettes/GOfuncR/inst/doc/GOfuncR.html) for an introduction.

Also refer to the man-pages for single functions, e.g.
```r
library(GOfuncR)
?go_enrich
?get_anno_categories

```
