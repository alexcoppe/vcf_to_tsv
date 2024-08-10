#include<iostream>
#include <fstream>
#include<getopt.h>
#include<list>
#include<algorithm>
#include "vcf.h"

class Vcf_with_genonotype: public Vcf{
    public:
        std::string format = "";
        std::string sample1 = "";
        std::string sample2 = "";
        std::map<std::string, std::string> sample1_map;
        std::map<std::string, std::string> sample2_map;

        Vcf_with_genonotype();
        Vcf_with_genonotype(std::string);
        void show();
    private:
        std::vector<std::string> sample1_vector;
        std::vector<std::string> sample2_vector;
        std::vector<std::string> format_vector;
        void build_samples();
};

