#ifndef fileio_H_INCLUDED
#define fileio_H_INCLUDED
#include <vector>
std::vector<std::string> readFile(std::string filename);
void saveFile(std::string filename, std::vector<std::string> lines);


#endif // FILEIO_H_INCLUDED
