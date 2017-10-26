#include <lang/Math.hpp>
#include <lang/Process.hpp>
#include <lang/System.hpp>
#include <lang/Runtime.hpp>
#include <io/File.hpp>
#include <io/FileInputStream.hpp>
#include <io/FileOutputStream.hpp>
#include <chrono>
#include <cstdlib>

using namespace std::chrono;

namespace lang {
const The_System System;
const The_Math Math;

void Shutdown::exit(int status) {
	std::exit(status);
}

static io::FileInputStream std_fin(std::cin);
static io::FileOutputStream std_fout(std::cout);
static io::FileOutputStream std_ferr(std::cerr);
static io::PrintStream std_out(std_fout);
static io::PrintStream std_err(std_ferr);

io::InputStream& The_System::in = std_fin;
io::PrintStream& The_System::out = std_out;
io::PrintStream& The_System::err = std_err;

jlong The_System::currentTimeMillis() {
	return duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
}

String The_System::getenv(const String& name) {
	const char *v = std::getenv(name.intern().c_str());
	if (v == null) return String();
	return v;
}

void The_System::exit(int code) { Runtime::getRuntime().exit(code); }
void The_System::gc() { Runtime::getRuntime().gc(); }

Process& ProcessBuilder::start() {
	Process *p = null;
	return *p;
}

Runtime Runtime::currentRuntime;

} //namespace lang

namespace io {
const String File::separator = "/";
}
