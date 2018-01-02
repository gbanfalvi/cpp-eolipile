//
// Created by Gabriel Banfalvi on 2018-01-01.
//

#ifndef PR_PLATFORMER_TESTING_H
#define PR_PLATFORMER_TESTING_H

#include <iostream>
#include <string>
#include <assert.h>

using namespace std;

// Shortcut to print to cout

// https://stackoverflow.com/a/27375675
template <typename Arg, typename... Args>
void printCout(Arg&& arg, Args&&... args)
{
    cout << forward<Arg>(arg);
    using expander = int[];
    (void)expander{0, (void(cout << std::forward<Args>(args)),0)...};
    cout << endl;
}

// Macros and methods for testing

string* ongoingTest = NULL;
int testSuccesses = 0;
int testFailures = 0;

void beginTestSection(string name) {

    if (ongoingTest != NULL) {
        printCout("Already testing ", &ongoingTest, ". End test section first.");
        assert(false);
    }
    ongoingTest = new string(name);
    printCout("🔷 Starting ", *ongoingTest);
    testSuccesses = 0;
    testFailures = 0;
}

void endTestSection() {
    int total = testSuccesses + testFailures;

    printCout("🔶 Finished ", *ongoingTest, ".");
    printCout("   ✅ Successes: ", testSuccesses, "/", total);
    printCout("   ❌ Failures:  ", testFailures, "/", total);
    delete ongoingTest;
    ongoingTest = NULL;
}

void logComment(string comment) {
    printCout("   📝 ", comment);
}

void logTest(bool success, string descr, string file, int line, string func, string expr) {
    if (success) {
        printCout("   ✅", " ", descr);
        testSuccesses += 1;
    } else {
        printCout("   ❌", " Failed: ", descr, " with ", expr);
        printCout("          at: ", file, ":", line);

        testFailures += 1;

    }
}

#define testTrue(e, d) (logTest(e ? true : false, d, __FILE__, __LINE__, __PRETTY_FUNCTION__, #e))



#endif //PR_PLATFORMER_TESTING_H
