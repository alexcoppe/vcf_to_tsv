#include<iostream>
#include <fstream>
#include<getopt.h>
#include<list>
#include<algorithm>
#include "vcf_with_genotype_info.h"


int main(int argc, char *argv[]){
    char c;
    int hflag = 0;
    char help[] = "Usage: get_pass_variants [OPTION]... VCF_file\n  "
                "-h\tshow help options";

    while ((c = getopt (argc, argv, "h")) != -1){
        switch (c) {
            case 'h':
                hflag = 1;
                puts(help);
                return 1;
            case '?':
                if (isprint(optopt))
                    fprintf(stderr, "Unknown option `-%c'.\n", optopt);
                else
                    fprintf(stderr, "Unknown option character `\\x%x'.\n", optopt);
                return 1;
            default:
                abort();
        }
    }

    argc -= optind;
    argv += optind;

    /* Check if there is a VCF file argument */
    if (argc < 2) {
        std::cout << "VCF file path not specified\n";
        return -1;
    }

    std::ifstream file(argv[0]);
    std::string line;
    int number_of_snpeff_variants = 0;

    std::list<std::string> wanted_fields;

    std::ifstream wanted_fields_file(argv[1]);
    if (wanted_fields_file.is_open()){
        while (getline(wanted_fields_file, line)){
            wanted_fields.push_back(line);
        }
    }

    Vcf_with_genonotype v;

    if (file.is_open()) {
        while (getline(file, line)){


            if (line[0] != '#'){
                if (line[0] != '#'){
                    try{
                        std::string::difference_type n = std::count(line.begin(), line.end(), '\t');
                        if (n < 8)
                            throw (n);
                    }
                    catch (std::string::difference_type n){
                        std::cout << "Error in this line:\n" << line << "\nthere are only " << n << " fileds\n";
                        return -1;
                    }
                    v = Vcf_with_genonotype(line);
                    std::string concatenated_line = "";
                    number_of_snpeff_variants = v.snpeff_annotation.size();
                    std::vector<std::string>transcripts_list;
                    for (int v = 0; v < number_of_snpeff_variants; v++)
                        transcripts_list.push_back("");

                    for (std::string field: wanted_fields){

                        if (field.find(':') != std::string::npos){
                            int position_of_separator = field.find(":");
                            std::string wanted_subfield = field.substr(position_of_separator + 1, field.length());
                            
                            int i = 0;
                            for (Ann_variant var: v.snpeff_annotation){
                                if (wanted_subfield == "putative_impact"){
                                    transcripts_list[i] = transcripts_list[i] + var.putative_impact + "\t";
                                }
                                else if (wanted_subfield == "gene_name"){
                                    transcripts_list[i] = transcripts_list[i] + var.gene_name + "\t";
                                }

                                else if (wanted_subfield == "allele"){
                                    transcripts_list[i] = transcripts_list[i] + var.allele + "\t";
                                }
                                else if (wanted_subfield == "annotation"){
                                    transcripts_list[i] = transcripts_list[i] + var.annotation + "\t";
                                }
                                else if (wanted_subfield == "gene_id"){
                                    transcripts_list[i] = transcripts_list[i] + var.gene_id + "\t";
                                }
                                else if (wanted_subfield == "feature_type"){
                                    transcripts_list[i] = transcripts_list[i] + var.feature_type + "\t";
                                }
                                else if (wanted_subfield == "feature_id"){
                                    transcripts_list[i] = transcripts_list[i] + var.feature_id + "\t";
                                }
                                else if (wanted_subfield == "transcript_biotype"){
                                    transcripts_list[i] = transcripts_list[i] + var.transcript_biotype + "\t";
                                }
                                else if (wanted_subfield == "rank"){
                                    transcripts_list[i] = transcripts_list[i] + var.rank + "\t";
                                }
                                else if (wanted_subfield == "hgvs_c"){
                                    transcripts_list[i] = transcripts_list[i] + var.hgvs_c + "\t";
                                }
                                else if (wanted_subfield == "hgvs_p"){
                                    transcripts_list[i] = transcripts_list[i] + var.hgvs_p + "\t";
                                }
                                else if (wanted_subfield == "cdna_position"){
                                    transcripts_list[i] = transcripts_list[i] + var.cdna_position + "\t";
                                }
                                else if (wanted_subfield == "cds_position"){
                                    transcripts_list[i] = transcripts_list[i] + var.cds_position + "\t";
                                }
                                if (wanted_subfield == "protein_position"){
                                    transcripts_list[i] = transcripts_list[i] + var.protein_position + "\t";
                                }
                                if (wanted_subfield == "distance_to_feature"){
                                    transcripts_list[i] = transcripts_list[i] + var.distance_to_feature + "\t";
                                }
                                if (wanted_subfield == "errors"){
                                    transcripts_list[i] = transcripts_list[i] + var.errors + "\t";
                                }
                                i++;
                            }
                        }
                        else if (field.find(';') != std::string::npos){
                            int position_of_separator = field.find(";");
                            std::string wanted_subfield = field.substr(position_of_separator + 1, field.length());

                            for (int i = 0; i < number_of_snpeff_variants; i++){
                                transcripts_list[i] = transcripts_list[i] + v.info_map[wanted_subfield] + "\t";
                            }
                        }
                        else if (field.find('|') != std::string::npos){
                            int position_of_separator = field.find("|");
                            std::string wanted_subfield = field.substr(position_of_separator + 1, field.length());

                            for (int i = 0; i < number_of_snpeff_variants; i++){
                                transcripts_list[i] = transcripts_list[i] + v.sample1_map[wanted_subfield] + "\t";
                                if (v.sample2_map.count(wanted_subfield) != 0)
                                    transcripts_list[i] = transcripts_list[i] + v.sample2_map[wanted_subfield] + "\t";
                            }
                        }
                        else if (field.find(':') == std::string::npos){
                            if (field == "chromosome"){
                                for (int i = 0; i < number_of_snpeff_variants; i++){
                                    transcripts_list[i] = transcripts_list[i] + v.chromosome + "\t";
                                }
                            }
                            else if (field == "position") {
                                for (int i = 0; i < number_of_snpeff_variants; i++){
                                    transcripts_list[i] = transcripts_list[i] + std::to_string(v.position) + "\t";
                                }
                            }
                            else if (field == "id") {
                                for (int i = 0; i < number_of_snpeff_variants; i++){
                                    transcripts_list[i] = transcripts_list[i] + v.id + "\t";
                                }
                            }
                            else if (field == "reference") {
                                for (int i = 0; i < number_of_snpeff_variants; i++){
                                    transcripts_list[i] = transcripts_list[i] + v.reference + "\t";
                                }
                            }
                            else if (field == "alternative") {
                                for (int i = 0; i < number_of_snpeff_variants; i++){
                                    transcripts_list[i] = transcripts_list[i] + v.alternative + "\t";
                                }
                            }
                            else if (field == "quality") {
                                for (int i = 0; i < number_of_snpeff_variants; i++){
                                    transcripts_list[i] = transcripts_list[i] + std::to_string(v.quality) + "\t";
                                }
                            }
                            else if (field == "filter") {
                                for (int i = 0; i < number_of_snpeff_variants; i++){
                                    transcripts_list[i] = transcripts_list[i] + v.filter + "\t";
                                }
                            }
                            else if (field == "info") {
                                for (int i = 0; i < number_of_snpeff_variants; i++){
                                    transcripts_list[i] = transcripts_list[i] + v.info + "\t";
                                }
                            }

                        }

                    }


                    for (int i = 0; i < number_of_snpeff_variants; i++){
                        std::cout << transcripts_list[i] << "\n";
                    }
                }
            }
        }
        file.close();
    }


    return 0;
}
