# Structures-in-C

This repo is made of two structures in C, a linked list and a stack. The development methodology is test-driven dev.
<ul>
  <li><b>The linked list:</b></li>
    <t>The linked list is generic and makes use of memory allocation. It supports the main features of a linked list and is tested using unit testing with the assistance of a static code analizator (klocwork) and memory checker (valgrind). The linked list is free of leaks and segementation faults.</t>
  <t>To show the linked list in a working manner, a memory manager is implemented. The memory manager is a separete structure that has both address and size and its functions are making use of the linked list. There is also a user interface in a separete header file to process data from the keyboard (at what address and with what size do we want to put a memory block). </t>
  <li><b>The stack:</b></li>
    <t>The stack is made into a shared library (.so). It supports the main features of the stack like push(), pop(), empty(), size(), etc. The makefile is made so that it compiles the source file into .so file. In folder "mystack" the makefile dynamically links to our libmystack.so file and implements two applications. The stack uses dynamic allocation with no leaks or seg faults.
      <ul>
        <li>Link list reverser</li>
        <t>This application is made to test if we will get any hard faults. It reverses 2000 items using a stack.</t>
        <li>Reverse polish notation calculator</li>
        <t>The Calculator supports the bais +, -, /, * with additon to sqrt and power of 2. The calculator supports up to 50 characters and has one stack for numbers and one for operators. </t>
      </ul>
      <t>The stack is tested with unit tests(unity), static code analizator (klocwork) and memory checker (valgrind).</t>
      </ul>
