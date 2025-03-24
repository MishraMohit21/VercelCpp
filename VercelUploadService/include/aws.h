#include <cstdlib>
#include <string>

bool uploadFileViaNode(const std::string& fileName, const std::string& localPath) {
  std::string command = "node ./node/upload-bridge.js \"" + fileName + "\" \"" + localPath + "\"";
  int result = system(command.c_str());
  return (result == 0); // Returns true if successful
}