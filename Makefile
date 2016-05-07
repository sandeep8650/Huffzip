OPTH=obj
SPTH=src
object=  $(OPTH)/huffzip.o \
		 $(OPTH)/compress.o \
		 $(OPTH)/decompress.o \
		 $(OPTH)/write_outfile.o \
		 $(OPTH)/count_frequency.o \
		 $(OPTH)/build_tree.o \
		 $(OPTH)/create_code_table.o \
		 $(OPTH)/delete_tree.o \
		 $(OPTH)/print_tree_preorder.o

huffzip: $(object)
	g++ $(CFLAGS) -o huffzip $(object)

$(OPTH)/huffzip.o: $(SPTH)/huffzip.cpp $(SPTH)/huffzip.h
	@if [ ! -d $(OPTH) ];then mkdir $(OPTH) ;fi
	g++ -c $(SPTH)/huffzip.cpp -o $(OPTH)/huffzip.o
	
$(OPTH)/compress.o: $(SPTH)/compress.cpp $(SPTH)/huffzip.h
	@if [ ! -d $(OPTH) ];then mkdir $(OPTH) ;fi
	g++ -c $(SPTH)/compress.cpp -o $(OPTH)/compress.o

$(OPTH)/decompress.o: $(SPTH)/decompress.cpp $(SPTH)/huffzip.h
	@if [ ! -d $(OPTH) ];then mkdir $(OPTH) ;fi
	g++ -c $(SPTH)/decompress.cpp -o $(OPTH)/decompress.o
	
$(OPTH)/write_outfile.o: $(SPTH)/write_outfile.cpp $(SPTH)/huffzip.h
	@if [ ! -d $(OPTH) ];then mkdir $(OPTH) ;fi
	g++ -c $(SPTH)/write_outfile.cpp -o $(OPTH)/write_outfile.o

$(OPTH)/count_frequency.o: $(SPTH)/count_frequency.cpp $(SPTH)/huffzip.h
	@if [ ! -d $(OPTH) ];then mkdir $(OPTH) ;fi
	g++ -c $(SPTH)/count_frequency.cpp -o $(OPTH)/count_frequency.o

$(OPTH)/build_tree.o: $(SPTH)/build_tree.cpp $(SPTH)/huffzip.h
	@if [ ! -d $(OPTH) ];then mkdir $(OPTH) ;fi
	g++ -c $(SPTH)/build_tree.cpp -o $(OPTH)/build_tree.o

$(OPTH)/create_code_table.o: $(SPTH)/create_code_table.cpp $(SPTH)/huffzip.h
	@if [ ! -d $(OPTH) ];then mkdir $(OPTH) ;fi
	g++ -c $(SPTH)/create_code_table.cpp -o $(OPTH)/create_code_table.o

$(OPTH)/delete_tree.o: $(SPTH)/delete_tree.cpp $(SPTH)/huffzip.h
	@if [ ! -d $(OPTH) ];then mkdir $(OPTH) ;fi
	g++ -c $(SPTH)/delete_tree.cpp -o $(OPTH)/delete_tree.o

$(OPTH)/print_tree_preorder.o: $(SPTH)/print_tree_preorder.cpp
	@if [ ! -d $(OPTH) ];then mkdir $(OPTH) ;fi
	g++ -c $(SPTH)/print_tree_preorder.cpp -o $(OPTH)/print_tree_preorder.o

clean:
	rm -f $(OPTH)/*.o huffzip
