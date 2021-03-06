#ifndef __LANG_RUNTIME_HPP
#define __LANG_RUNTIME_HPP

#include <lang/Thread.hpp>
#include <lang/Process.hpp>
#include <util/ArrayList.hpp>
#include <util/StringTokenizer.hpp>

namespace lang {

class Shutdown final {
	friend class Runtime;
	static void exit(int status);
	static void halt(int status);
};

class Runtime : extends Object {
private:
	static io::File null_file;
	static Runtime currentRuntime;
public:
	static Runtime& getRuntime() { return currentRuntime; }
	void exit(int status) {Shutdown::exit(status);}
	void halt(int status) {Shutdown::halt(status);}
	void addShutdownHook(Thread hook) { }
	boolean removeShutdownHook(Thread hook) {return false;}
	Process& exec(String command) {
		return exec(command, null, null_file);
	}
	Process& exec(String command, util::List<String> *envp) {
		return exec(command, envp, null_file);
	}
	Process& exec(String command, util::List<String> *envp, io::File dir) {
		if (command.length() == 0)
			throw IllegalArgumentException("Empty command");
		StringTokenizer st = StringTokenizer(command);
		ArrayList<String> cmdarray;
		for (int i = 0; st.hasMoreTokens(); ++i)
			cmdarray.add(st.nextToken());
		return exec(cmdarray, envp, dir);
	}
	Process& exec(util::List<String>& cmdarray) {
		return exec(cmdarray, null, null_file);
	}
	Process& exec(util::List<String>& cmdarray, util::List<String> *envp) {
		return exec(cmdarray, envp, null_file);
	}
	Process& exec(util::List<String>& cmdarray, util::List<String> *envp, io::File dir) {
		return ProcessBuilder(cmdarray)
			.environment(envp)
			.directory(dir)
			.start();
	}
	int availableProcessors();
	long freeMemory() {return 0;}
	long totalMemory() {return 0;}
	long maxMemory() {return 0;}
	void gc() {}
	void runFinalization() {}
	void traceInstructions(boolean on) {}
	void traceMethodCalls(boolean on) {}
	void load(String filename) {}
	void loadLibrary(String libname) {}
};

} //namespace lang


#endif
