#include "../../include/despot/util/logging.h"
// #include <thread>

using namespace std;

namespace despot {

const string logging::markers_[] = { "NONE", "ERROR", "WARN", "INFO", "DEBUG",
	"VERBOSE" };
const int logging::NONE_ = 0;
const int logging::ERROR_ = 1;
const int logging::WARN_ = 2;
const int logging::INFO_ = 3;
const int logging::DEBUG_ = 4;
const int logging::VERBOSE_ = 5;

log_ostream::log_ostream(ostream& out, string marker) :
	ostream(&buffer_),
	buffer_(out, marker) {
}

log_ostream::log_buf::log_buf(ostream& out, string marker) :
	out_(out),
	marker_(marker) {
}

log_ostream::log_buf::~log_buf() {
	// pubsync();
}

streambuf* log_ostream::log_buf::setbuf(char* s, streamsize n) {
	return this;
}

int log_ostream::log_buf::sync() {
	//NOTE: disabled c++11 feature
	// out_ << marker_ << "-" << this_thread::get_id() << ": " << str();
	out_ << marker_ << ": " << str();
	str("");
	return !out_;
}

int logging::verbosity_ = ERROR_;

void logging::level(int verbosity) {
	verbosity_ = verbosity;
}

int logging::level() {
	return verbosity_;
}

log_ostream& logging::stream(int level) {
	return *(streams_[level]);
}

void logging::stream(int level, ostream& out) {
	if (level >= ERROR_ && level <= VERBOSE_) {
		streams_[level] = new log_ostream(out, markers_[level]);
	}
}

vector<log_ostream*> logging::InitializeLogStreams() {
	vector<log_ostream*> streams(6);

	streams[NONE_] = NULL;
	streams[ERROR_] = new log_ostream(cerr, markers_[ERROR_]);
	streams[WARN_] = new log_ostream(cerr, markers_[WARN_]);
	streams[INFO_] = new log_ostream(cerr, markers_[INFO_]);
	streams[DEBUG_] = new log_ostream(cerr, markers_[DEBUG_]);
	streams[VERBOSE_] = new log_ostream(cerr, markers_[VERBOSE_]);

	return streams;
}

vector<log_ostream*> logging::streams_ = logging::InitializeLogStreams();

} // namespace despot
