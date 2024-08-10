#include<iostream>
#include <fstream>
#include<getopt.h>
#include<list>
#include<algorithm>
#include "vcf.h"


Vcf::Vcf(){
    chromosome = "";
    position = 0;
    id = "";
    reference = "";
    alternative = "";
    quality = 0;
    filter = ".";
    info = ".";
}

Vcf::Vcf(std::string l){
    size_t pos = 0;
    std::string token;
    std::list<std::string> fields;
    int i = 0;

    while ((pos = l.find("\t")) != std::string::npos){
        token = l.substr(0, pos);

        if (i == 0)
            chromosome = token;
        if (i == 1)
            position = stoi(token);
        if (i == 2)
            id = token;
        if (i == 3)
            reference = token;
        if (i == 4)
            alternative = token;
        if (i == 5){
            if (token == ".")
                quality = 0;
            else
                quality = std::stof(token);
        }
        if (i == 6)
            filter = token;
        if (i == 7)
            info = token;

        fields.push_back(token);
        l = l.substr(pos + 1, l.length());
        i++;
    }

    token = l.substr(pos + 1, l.length());
    fields.push_back(token);

    build_info_map();
    build_ann();
 
}


Vcf::Vcf(std::string chr, int pos, std::string genomic_id, std::string ref, std::string alt,
        float qual, std::string filt, std::string inf){
    chromosome = chr;
    position = pos;
    id = genomic_id;
    reference = ref;
    alternative = alt;
    quality = qual;
    filter = filt;
    info = inf;
}

void Vcf::show(){
    std::cout << "Chromosome: " << chromosome << "\n";
    std::cout << "Position: " << position << "\n";
    std::cout << "Id: " << id << "\n";
    std::cout << "Ref: " << reference << "\n";
    std::cout << "Alt: " << alternative << "\n";
    std::cout << "Quality: " << quality << "\n";
    std::cout << "Filter: " << filter << "\n";
    std::cout << "Info: " << info << "\n";
}

void Vcf::build_info_map(){
    size_t pos = 0;
    std::string token;
    std::string key;
    std::string value;

    while ((pos = info.find(";")) != std::string::npos){
        token = info.substr(0, pos);
        key = token.substr(0, token.find('='));
        value = token.substr(token.find('=') + 1, token.length());
        info = info.substr(pos + 1, info.length());
        info_map[key] = value;
    }

    token = info.substr(pos + 1, info.length());
    key = token.substr(0, token.find('='));
    value = token.substr(token.find('=') + 1, token.length());
    info = info.substr(pos + 1, info.length());
    info_map[key] = value;
}

void Vcf::build_ann(){
    std::string all_annotated_transcripts = info_map["ANN"];
    size_t pos = 0;
    std::string token;

    //Possible bug. To check with a vcf without snpeff annotation
    if (all_annotated_transcripts.find(",") == std::string::npos){
        Ann_variant variant = Ann_variant(all_annotated_transcripts);
        snpeff_annotation.push_back(variant);
    }
    else {
        while ((pos = all_annotated_transcripts.find(",")) != std::string::npos){
            token = all_annotated_transcripts.substr(0, pos);
            Ann_variant variant = Ann_variant(token);
            snpeff_annotation.push_back(variant);
            all_annotated_transcripts = all_annotated_transcripts.substr(pos + 1, all_annotated_transcripts.length());
        }


        token = all_annotated_transcripts.substr(pos + 1, all_annotated_transcripts.length());
        Ann_variant variant = Ann_variant(token);
        snpeff_annotation.push_back(variant);
 
    }


}
