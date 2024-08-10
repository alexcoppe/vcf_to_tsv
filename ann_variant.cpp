#include<iostream>
#include <fstream>
#include<getopt.h>
#include<list>
#include<algorithm>
#include "ann_variant.h"


Ann_variant::Ann_variant(){
}

Ann_variant::Ann_variant(std::string var){
    size_t pos = 0;
    std::string token;
    int i = 1;

    while ((pos = var.find("|")) != std::string::npos){
        if (i > 16)
            break;
        token = var.substr(0, pos);
        if ((i - 1) == 0)
            allele = token;
        if ((i - 1) == 1)
            annotation = token;
        if ((i - 1) == 2)
            putative_impact = token;
        if ((i - 1) == 3)
            gene_name = token;
        if ((i - 1) == 4)
            gene_id = token;
        if ((i - 1) == 5)
            feature_type = token;
        if ((i - 1) == 6)
            feature_id = token;
        if ((i - 1) == 7)
            transcript_biotype = token;
        if ((i - 1) == 8)
            rank = token;
        if ((i - 1) == 9)
            hgvs_c = token;
        if ((i - 1) == 10)
            hgvs_p = token;
        if ((i - 1) == 11)
            cdna_position = token;
        if ((i - 1) == 12)
            cds_position = token;
        if ((i - 1) == 13)
            protein_position = token;
        if ((i - 1) == 14)
            distance_to_feature = token;
        var = var.substr(pos + 1, var.length());
        i++;
    }
    

    token = var.substr(pos + 1, var.length());
    errors = token;
}

void Ann_variant::print_variant_annotation(){
    std::cout << allele << "\n";
    std::cout << annotation << "\n";
    std::cout << putative_impact << "\n";
    std::cout << gene_name << "\n";
    std::cout << gene_id << "\n";
    std::cout << feature_type << "\n";
    std::cout << feature_id << "\n";
    std::cout << transcript_biotype << "\n";
    std::cout << rank << "\n";
    std::cout << "hgvs_c: " << hgvs_c << "\n";
    std::cout << "hgvs_p: " << hgvs_p << "\n";
    std::cout << "cDNA_position: " << cdna_position << "\n";
    std::cout << "CDS_position: " << cds_position << "\n";
    std::cout << "Protein_position: " << protein_position << "\n";
    std::cout << "Distance to feature: " << distance_to_feature << "\n";
    std::cout << "Errors: " << errors << "\n";
    std::cout << "\n";
}
