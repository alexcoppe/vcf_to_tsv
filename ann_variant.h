#include<iostream>
#include <fstream>
#include<getopt.h>
#include<list>
#include<algorithm>
#include<map>


class Ann_variant{
    public:
        std::string allele;
        std::string annotation;
        std::string putative_impact;
        std::string gene_name;
        std::string gene_id;
        std::string feature_type;
        std::string feature_id;
        std::string transcript_biotype;
        std::string rank;
        std::string hgvs_c;
        std::string hgvs_p;
        std::string cdna_position;
        std::string cds_position;
        std::string protein_position;
        std::string distance_to_feature;
        std::string errors;

        Ann_variant();
        Ann_variant(std::string);
        void print_variant_annotation();
}; 


