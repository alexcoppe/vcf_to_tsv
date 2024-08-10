#include<iostream>
#include <fstream>
#include<getopt.h>
#include<list>
#include<algorithm>
#include "vcf_with_genotype_info.h"
#include<array>


Vcf_with_genonotype::Vcf_with_genonotype(): Vcf(){
}

Vcf_with_genonotype::Vcf_with_genonotype(std::string l) : Vcf(l){
    //Vcf_with_genonotype::Vcf_with_genonotype(std::string s){
    //
    size_t pos = 0;
    std::string token;
    //std::list<std::string> fields;
    int i = 0;

    while ((pos = l.find("\t")) != std::string::npos){
        token = l.substr(0, pos);

        if (i == 8){
            format = token;
            //std::cout << format << "\n";
        }
        if (i == 9){
            sample1 = token;
            //std::cout << sample1 << "\n";
        }

        //fields.push_back(token);
        l = l.substr(pos + 1, l.length());
        i++;
    }

    token = l.substr(pos + 1, l.length());
    //fields.push_back(token);

    if (sample1 != ""){
        sample2 = token;
    }
    else{
        sample1 = token;
    }
    //std::cout << sample1 << "\n";
    //std::cout << sample2 << "\n\n";

    build_samples();

 
}

void Vcf_with_genonotype::build_samples(){
    int s2 = 0;
    int f = std::count(format.begin(), format.end(), ':');
    int s1 = std::count(sample1.begin(), sample1.end(), ':');
    if (sample2 != ""){
        s2 = std::count(sample2.begin(), sample2.end(), ':');
    }

    size_t pos = 0;
    std::string token;

    while ((pos = sample1.find(":")) != std::string::npos){
        token = sample1.substr(0, pos);
        sample1_vector.push_back(token);
        sample1 = sample1.substr(pos + 1, sample1.length());
    }

    token = sample1.substr(pos + 1, sample1.length());
    sample1_vector.push_back(token);
    
    std::string tokenf;
    pos = 0;
    while ((pos = format.find(":")) != std::string::npos){
        tokenf = format.substr(0, pos);
        format_vector.push_back(tokenf);
        format = format.substr(pos + 1, format.length());
    }

    tokenf = format.substr(pos + 1, format.length());
    format_vector.push_back(tokenf);

    if (sample2 != ""){
        std::string tokenf2;
        pos = 0;
        while ((pos = sample2.find(":")) != std::string::npos){
            tokenf2 = sample2.substr(0, pos);
            sample2_vector.push_back(tokenf2);
            sample2 = sample2.substr(pos + 1, sample2.length());
        }

        tokenf2 = sample2.substr(pos + 1, sample2.length());
        sample2_vector.push_back(tokenf2);
    }

    int j = 0;
    while (j < sample1_vector.size()){
        sample1_map[format_vector[j]] = sample1_vector[j];

        if (sample2 != ""){
            sample2_map[format_vector[j]] = sample2_vector[j];
        }
        j++;
    }
 
}

void Vcf_with_genonotype::show(){
    Vcf::show();
    std::cout << "Format: " << format << "\n";
    std::cout << "Sample 1: " << sample1 << "\n";
    std::cout << "Sample 2: " << sample2 << "\n";
}
