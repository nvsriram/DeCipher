# DeCipher
<strong>DeCipher</strong> is a user-friendly variable cipher with a <i title = "*wink wink*">catch</i>.

<p>This will work on <i>most</i> C++ IDEs. Just download the header files and add them all to the same folder as the .cpp file, compile and run! <em>NOTE: You may have to change library paths in order to read the <code>large.txt</code> dictionary text file.</em> <br>
  <i>P.S. You can replace the clearscreen.hpp and <code>ClearScreen()</code> function header file with <code title="Not recommended">system("clear");</code><t>,<code title="Also not recommended">system("cls");</code>,<code title="Recommended if you know to use it">&ltcurses.h&gt</code> library or any OS specific clear screen command. The <code>ClearScreen()</code> function currently implements a <q>flush-endlines-till-it-exceeds-screen-dimensions</q> approach to achieve the same result as any of the previously mentioned options.</i><br></p>
<p> <code>&ltasciiarmor.hpp&gt</code>, <code>&ltcaesar.hpp&gt</code> and <code>&ltvigenere.hpp&gt</code> header files correspond to their respective cipher and their implementation. It also defines a namespace that makes them easy to use. <code>&ltclearscreen.hpp&gt</code> header file defines one clear screen function that is used and two others that work based on the OS and included header files. <code>&ltdictionary.hpp&gt</code> header file implements the dictionary spellchecker by using the <code>large.txt</code> text file as its source file for the dictionary.<br>
  
  The program is very user-friendly and interactive. It starts by leading you to a pretty table of the various ciphers to choose from:</p>
<dl>
  <dt>ASCII armor</dt>
  <dd>ASCII armor is a binary-to-textual encoding converter. ASCII armor is a feature of a type of encryption called pretty good privacy (PGP). In this you are asked to enter the plaintext(<code>std::string</code>) and a key(<code>long int</code>). The function then:    
    <ol>
      <li>Creates pseudo-random hashing key derived from the key</li>
      <li>Uses the hashing key to encrypt the plaintext</li>
      <li>Converts to <code title="85 printable characters">Base85</code> to get a console-printable ciphertext</li>
    </ol>
    
  The function also decodes said ciphertext and converts it back to plaintext. A good proof of execution of the program would have your initially entered plaintext match the decoded text.
  </dd>
  
  <dt>Caesar Cipher</dt>
  <dd>Caesar cipher is one of the earliest known and simplest ciphers. It is a type of replacement cipher in which each letter of the plaintext is 'moved' to a certain place under the alphabet. For example, with a shift of 1, A will be replaced by B, B becomes C, and so on until it cycles back to A. In this you are asked to enter the plaintext(<code>std::string</code>) and a <i title="no negatives">whole</i> number key(<code>std::size_t</code>). Based on the key, the program would perform one of the following:
    <ol>
      <li>If they key is greater than 0, then treat the plaintext for what it is and perform the encryption and decryption shift based on the key</li>
      <li>If the key is 0, then treat the plaintext as a ciphertext and perform decryption using <i title="0, 1, ... 25">every possible key</i>. Then perform the <em title="Explained later">Bruteforce Dictionary</em> to find the possible plaintexts.</li>
    </ol>
  </dd>
  
  <dt>Vigenère Cipher</dt>
  <dd>The Vigenère cipher is a method of encrypting alphabetic text by using a series of interwoven Caesar ciphers, based on the letters of a keyword. It employs a form of polyalphabetic substitution. In this you are asked to enter the plaintext(<code>std::string</code>)and a alphabetic key(<code>std::string</code>). The program ignores case and assigns every alphabet to a shift value. For example, A/a is a shift of 0, B/b is a shift of 1 and so on. Based on the key, the function then:
  <ol>
    <li>Shifts the first character of the plaintext by the shift determined by first character of the key. Second character will be shifted based on second character of key and so on.</li>
    <li>If the key is longer than plaintext, it'll move until plaintext length and be shifted by the characters that come under that length of key. However, if the plaintext is longer than the key, then the key repeats until plaintext has reached its end.</li>
  </ol>
</dd>

<dt>Bruteforce Dictionary</dt>
<dd>Although this is not a direct choice, it is an important part of the project. The Bruteforce Dictionary is used to implement a dictionary as a spellchecker to crack the plaintext for the Caesar cipher in this program but can be used for the other ciphers as well. This works as follows:
  <ol>
    <li>First the dictionary is loaded from the file into a hashtable dynamically indexed by the first letters of the word. Hence we get <i title="A to Z">twenty-six</i> <q>heads</q> for the linked lists.</li>
    <li>Then the inputted ciphertext is decoded with a key that loops from 0 to 25. This way we get every possible input for the given output.</li>
    <li>Based on the input at every iteration, it is checked with the linked list corresponding to the first letter of the input. If it is present, it is displayed along with the key corresponding to the result.</li>
  </ol>
  In this manner, we manage to arrive at the logical input corresponding to the given output using bruteforce.
</dd>
</dl></p>
<p>Just enter your choice, follow the instructions, and you should be good to <i title="Terms and conditions apply">go</i>!<br>
Enjoy!¯\_(ツ)_/¯</p>

