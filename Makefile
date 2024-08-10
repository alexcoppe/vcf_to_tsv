all: vcf_to_tsv

CC=g++

ann_variant.o: ann_variant.cpp
	$(CC) -std=c++11 -c ann_variant.cpp
vcf.o: vcf.cpp
	$(CC) -std=c++11 -c vcf.cpp
vcf_to_tsv: vcf_to_tsv.o vcf_with_genotype_info.o vcf.o ann_variant.o
	$(CC) -std=c++11 vcf_to_tsv.o ann_variant.o  vcf_with_genotype_info.o vcf.o -o vcf_to_tsv
vcf_with_genotype_info.o: vcf_with_genotype_info.cpp
	$(CC) -std=c++11 -c vcf_with_genotype_info.cpp
vcf_to_tsv.o: vcf_to_tsv.cpp
	$(CC) -std=c++11 -c vcf_to_tsv.cpp
clean:
	rm -rf *.o vcf_to_tsv
