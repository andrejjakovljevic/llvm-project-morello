"""
Test lldb watchpoint that uses '-s size' to watch a pointed location with size.
"""

from __future__ import print_function

import lldb_shared

import os, time
import re
import lldb
from lldbtest import *
import lldbutil

class HelloWatchLocationTestCase(TestBase):

    mydir = TestBase.compute_mydir(__file__)

    def setUp(self):
        # Call super's setUp().
        TestBase.setUp(self)
        # Our simple source filename.
        self.source = 'main.cpp'
        # Find the line number to break inside main().
        self.line = line_number(self.source, '// Set break point at this line.')
        # This is for verifying that watch location works.
        self.violating_func = "do_bad_thing_with_location";
        # Build dictionary to have unique executable names for each test method.
        self.exe_name = self.testMethodName
        self.d = {'CXX_SOURCES': self.source, 'EXE': self.exe_name}

    @expectedFailureAndroid(archs=['arm', 'aarch64']) # Watchpoints not supported
    @expectedFailureWindows("llvm.org/pr24446") # WINDOWS XFAIL TRIAGE - Watchpoints not supported on Windows
    def test_hello_watchlocation(self):
        """Test watching a location with '-s size' option."""
        self.build(dictionary=self.d)
        self.setTearDownCleanup(dictionary=self.d)
        exe = os.path.join(os.getcwd(), self.exe_name)
        self.runCmd("file " + exe, CURRENT_EXECUTABLE_SET)

        # Add a breakpoint to set a watchpoint when stopped on the breakpoint.
        lldbutil.run_break_set_by_file_and_line (self, None, self.line, num_expected_locations=1, loc_exact=False)

        # Run the program.
        self.runCmd("run", RUN_SUCCEEDED)

        # We should be stopped again due to the breakpoint.
        # The stop reason of the thread should be breakpoint.
        self.expect("thread list", STOPPED_DUE_TO_BREAKPOINT,
            substrs = ['stopped',
                       'stop reason = breakpoint'])

        # Now let's set a write-type watchpoint pointed to by 'g_char_ptr'.
        # The main.cpp, by design, misbehaves by not following the agreed upon
        # protocol of using a mutex while accessing the global pool and by not
        # incrmenting the global pool by 2.
        self.expect("watchpoint set expression -w write -s 1 -- g_char_ptr", WATCHPOINT_CREATED,
            substrs = ['Watchpoint created', 'size = 1', 'type = w'])
        # Get a hold of the watchpoint id just created, it is used later on to
        # match the watchpoint id which is expected to be fired.
        match = re.match("Watchpoint created: Watchpoint (.*):", self.res.GetOutput().splitlines()[0])
        if match:
            expected_wp_id = int(match.group(1), 0)
        else:
            self.fail("Grokking watchpoint id faailed!") 

        self.runCmd("expr unsigned val = *g_char_ptr; val")
        self.expect(self.res.GetOutput().splitlines()[0], exe=False,
            endstr = ' = 0')

        self.runCmd("watchpoint set expression -w write -s 4 -- &threads[0]")

        # Use the '-v' option to do verbose listing of the watchpoint.
        # The hit count should be 0 initially.
        self.expect("watchpoint list -v",
            substrs = ['hit_count = 0'])

        self.runCmd("process continue")

        # We should be stopped again due to the watchpoint (write type), but
        # only once.  The stop reason of the thread should be watchpoint.
        self.expect("thread list", STOPPED_DUE_TO_WATCHPOINT,
            substrs = ['stopped',
                       'stop reason = watchpoint %d' % expected_wp_id])

        # Switch to the thread stopped due to watchpoint and issue some commands.
        self.switch_to_thread_with_stop_reason(lldb.eStopReasonWatchpoint)
        self.runCmd("thread backtrace")
        self.expect("frame info",
            substrs = [self.violating_func])

        # Use the '-v' option to do verbose listing of the watchpoint.
        # The hit count should now be 1.
        self.expect("watchpoint list -v",
            substrs = ['hit_count = 1'])

        self.runCmd("thread backtrace all")
