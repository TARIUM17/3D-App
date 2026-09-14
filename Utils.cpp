#include "Utils.h"

using namespace std;

void checkCreateWindow(GLFWwindow* window) {
	if (!window) {
		std::cout << "== Failing Creating Window ==";
		glfwTerminate();
		exit(-1);
	}
}