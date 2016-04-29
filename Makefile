OPTH=obj
SPTH=src

huffzip: $(OPTH)/huffzip.o \
		 $(OPTH)/compress.o \
		 $(OPTH)/decompress.o \
		 $(OPTH)/write_outfile.o \
		 $(OPTH)/count_frequency.o \
		 $(OPTH)/build_tree.o \
		 $(OPTH)/create_code_table.o \
		 $(OPTH)/delete_tree.o \
		 $(OPTH)/print_tree_preorder.o
	g++ $(CFLAGS) -o huffzip  $(OPTH)/huffzip.o \
							  $(OPTH)/compress.o \
							  $(OPTH)/decompress.o \
							  $(OPTH)/write_outfile.o \
							  $(OPTH)/count_frequency.o \
							  $(OPTH)/build_tree.o \
							  $(OPTH)/create_code_table.o \
							  $(OPTH)/delete_tree.o \
							  $(OPTH)/print_tree_preorder.o

$(OPTH)/huffzip.o: $(SPTH)/huffzip.cpp $(SPTH)/huffzip.h
	g++ -c $(SPTH)/huffzip.cpp
	mv *.o $(OPTH)/
	
$(OPTH)/compress.o: $(SPTH)/compress.cpp $(SPTH)/huffzip.h
	g++ -c $(SPTH)/compress.cpp
	mv *.o $(OPTH)/

$(OPTH)/decompress.o: $(SPTH)/decompress.cpp $(SPTH)/huffzip.h
	g++ -c $(SPTH)/decompress.cpp
	mv *.o $(OPTH)/

$(OPTH)/write_outfile.o: $(SPTH)/write_outfile.cpp $(SPTH)/huffzip.h
	g++ -c $(SPTH)/write_outfile.cpp
	mv *.o $(OPTH)/

$(OPTH)/count_frequency.o: $(SPTH)/count_frequency.cpp $(SPTH)/huffzip.h
	g++ -c $(SPTH)/count_frequency.cpp
	mv *.o $(OPTH)/

$(OPTH)/build_tree.o: $(SPTH)/build_tree.cpp $(SPTH)/huffzip.h
	g++ -c $(SPTH)/build_tree.cpp
	mv *.o $(OPTH)/

$(OPTH)/create_code_table.o: $(SPTH)/create_code_table.cpp $(SPTH)/huffzip.h
	g++ -c $(SPTH)/create_code_table.cpp
	mv *.o $(OPTH)/

$(OPTH)/delete_tree.o: $(SPTH)/delete_tree.cpp $(SPTH)/huffzip.h
	g++ -c $(SPTH)/delete_tree.cpp
	mv *.o $(OPTH)/

$(OPTH)/print_tree_preorder.o: $(SPTH)/print_tree_preorder.cpp
	g++ -c $(SPTH)/print_tree_preorder.cpp
	mv *.o $(OPTH)/

clean:
	rm -f $(OPTH)/*.o huffzip
