# 2dx_extract
Extracts WAV files from Beatmania IIDX AC .2dx Archive Files (Tested on Beatmania IIDX 22 PENDUAL)

Made this in about an hour in C (I probably should have done it in C++). Apparently Beatmania IIDX's Arcade Audio files are not encrypted and are stored in a .2dx archive file which the game extracts whenever the user wants to play the song. These files are all WAVs (I do not understand why the modern rips of IIDX songs are in OGG). If you want keysounds from IIDX (Up to PENDUAL), get the HDD and extract the keysounds using this tool.

<h2>The .2dx Format</h2>
It is a container format. Nothing special. After looking at the bytes in a Hex Editor (HxD, for the record), each file information header begins with the bytes 0x32 0x44 0x58 0x39 (2DX9). If we skip ahead 8 bytes, we can get the file's size, which is a 32 bit integer. 12 bytes past the filesize is the actual file.

Traversing the file to find these is as simple as running a for-loop throughout the entire file until you find a 2DX9 header. It is guaranteed to work in this case because we skip the entire file after finding out it exists to check for more files, eliminating the possibility of a "2DX9" in a WAV file being found. The result of skipping bytes? A <i>really</i> fast and efficient program. :)

<h2>Compilation</h2>
<b>Linux (And probably Mac)</b>
Type "make" in the terminal... It's that easy.

<b>Windows</b>
Open up your favourite IDE (Like Visual Studio) and drag the files in and let it compile it for you. Since I was feeling generous, I compiled it for you too. Go into the "bin" folder and just download the EXE there. <a href = "https://github.com/iDestyKK/2dx_extract/blob/master/bin/2dx_extract.exe?raw=true" target = "_blank">Or if you are really feeling lazy... here you go.</a>

<h2>How to use</h2>
In Linux (And probably Mac), open up your terminal. In Windows, open up the Command Prompt.
Type the name of the executable. In this case, "2dx_extract". In Linux, you may have to type "./2dx_extract". It will tell you how to use the program.

The syntax is as follows:
2dx_extract [options] [.2dx file]

These are the following options you have at your disposal:
<ul>
<li>h - Shows help</li>
<li>i - Shows .2dx archive info (Without Extracting)</li>
<li>v - Verbose</li>
<li>V - Super Verbose (Shows more information)</li>
</ul>

<b>Note</b>: The .2dx archive MUST go last whenever specifying command line arguments.</br></br>
<b>Note</b>: Files extracted will be in your working directory.</br>
</br>
<b>Example:</b> 2dx_extract -V 22054.2dx<i></br>&nbsp;&nbsp;&nbsp;&nbsp;- Enables "Super Verbose" and extracts contents from "22054.2dx".</i>
</br></br>
<b>Example:</b> 2dx_extract -i 22054.2dx<i></br>&nbsp;&nbsp;&nbsp;&nbsp;- Gives information about "22054.2dx" without extracting the files.</i>
