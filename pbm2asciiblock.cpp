/* (View this document with a fixed-width ( i.e. mono-spaced) font. e.g. "Courier New")
+-------------------------------------------------------------------------------------+
|	This work is a BankOfDogeland product and is licensed under a 					  |
| 	Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License   |
| 	http://creativecommons.org/licenses/by-nc-sa/4.0/								  |
| 	20160922 Created by D.Reynolds													  |
| 	20160924 Build Version															  |
+-------------------------------------------------------------------------------------+

                                         ▗▖ ▗▖                        
        ▟█           ▄██▄                █▌ █▌▗█▌   ▐█           █▌   
        ▟▛           ▝ ▜█                     ▗█▘   █▛          ▐█▘   
  ▐█▟█▖ ███▌ █▙█▙██▖   █▛  ▟██▌▗▟█▙ ▗██▖██▌██▌▐███  █▌ ▄██▖ ▗██▖▐█▘▟▖ 
  ▐█▝█▌▗█▌▜█ █▛▐█ █▌  ▟▛  ▟█▘▟▘▐█▖▘▗█▌▝ ▐█ ▐█ ██▝█▌▗█▌▗█▘█▌▗█▌▝ ▐██▛  
  ▟▛ █▌▐█ ▐█▗█▌▟█▐█▌ ▟█   █▌▗█  ▜█▖▐█   ▐█ ▐█ █▌ █▌▐█ ▐█ █▌▐█   ▟██   
  █▙██ ▐█▟█▘▐█ █▌▐█ ▟█▙▄▖ █▙▟█ ▟▄█▌▐█▙▟ █▛ █▛▗█▙█▛ ▐█ ▐█▟█ ▐█▙▟ ██▐▙  
  █▛▀  ▀▝▀▘ ▝▀ ▀▘▝▀ ▀▀▀▀▘ ▝▀▘▀ ▝▀▘  ▝▀▘ ▀▘ ▀▘▝▘▀▀   ▀▘ ▀▀   ▝▀▘ ▀▘ ▀▘ 
 ▐█    										       
 ▝▀ (Above logo is an example program output)                                                                    
  

DOCUMENTATION
	1. WHAT IS THIS? (i.e. What does it do?)
	2. WHY DOES IT EXIST? (i.e. What problem does it solve?)
	3. HOW IS IT USED?
	4. HOW DOES IT WORK?
	5. USAGE TIPS
	6. MISCELLANEOUS NOTES
	7. GALLERY OF EXAMPLES

1. WHAT IS THIS?
	"pbm2asciiblock" is a program written in C++ which converts a plain Portable BitMap (PBM) format image into an 
	American Standard Code for Information Interchange (ASCII) text image comprised of ASCII block characters.

2. WHY DOES IT EXIST?
	This program is useful for converting 1-bit images (i.e. 2 colour images) into a text equivalent.
	The text version of the image can be easily used within command line interfaces (CLIs) where images cannot be displayed.
	This can be useful within the following scenarios, and others:
		Linux shell script art or logos,
		Bulletin Board System (BBS) titles,
		Figlet style art from photos,
		Fast drafts for Demo scene ANSI art,
		Picture display in monochrome text only chat or forum systems,
		Embedded systems (e.g. Raspberry Pi, Adafruit, Arduino, etc),
		and others where a text only display is available and pictures are desired.

3. HOW IS IT USED?
	Compile the code, then run it using a plain PBM image as the command argument:
	
	Ensure the C++ compiler and make installed.
	e.g. On a Linux Ubuntu operating system at the terminal command prompt ($)
		$ sudo apt-get install g++
		$ sudo apt-get install make
	
	Compile automatically with g++ using the "make" command,
		$ make pbm2asciiblock
	Make will automatically run the equivalent command of
		$ g++     pbm2asciiblock.cpp   -o pbm2asciiblock	
	
	This results in the executable pbm2asciiblock, which can be run with an input PBM file as a mandatory argument,
		$ ./pbm2asciiblock input_filename.pbm
	
	where input_filename.pbm is the name of your PBM image. Program output would be to the standard output (normally the terminal screen).
	If the output is preferred in a text file it can be redirected:
		$ ./pbm2asciiblock input.pbm > output.txt

			
4. HOW DOES IT WORK?
	THEORY OF METHOD
		ASCII block characters (Unicode range U+2580 to U+259F) contain characters that fill each quadrant of a character, and all possible combinations
		of these quadrants. When combined with the space character this gives 16 combinations that enable a single character block to textually
		represent a 2x2 pixel region.
	
	PRACTICAL IMPLEMENTATION
		The bit data in the image is read into an 2D array.
		This array is then read as 2x2 pixel regions, and the block which resembles the 2x2 pixel region is returned 
		as the ASCII block for that 2x2 pixel region in the PBM image. This ASCII block is written to standard out as a block of the ASCII image
		before the next 2x2 pixel region is read. This reading and writing cycle is repeated until the entire image has been processed.

		The ASCII image is half the dimensions of the PBM image, since each ASCII block represents a 2x2 pixel region.
		If the original image dimensions are an odd number (2N+1) the ASCII image will effectively need half a block of padding added to the right
		or bottom of the image, since half of the PBM image (N+0.5) would result in 0.5 of an ASCII character, which is not possible.
		So the padding is added to prevent the ASCII image edge being cut off.

	ENCODING FOR THIS IMPLEMENTATION:
		For a 2x2 pixel region each pixel (when "on") is given a value 1, 2, 4, or 8 depending on it's position:
		[1][2]
		[4][8]
		When the pixel is "off" the value given is zero.
		The sum of the given values determines the matching ASCII block to represent the 2x2 region.
		
		(Value = Sum of pixel values)
		Value 	Code 	Character 	Description
		00   	U+0020				SPACE
		01   	U+2598 	▘ 			Quadrant upper left
		02   	U+259D 	▝ 			Quadrant upper right
		03   	U+2580 	▀ 			Upper half block
		04   	U+2596 	▖ 			Quadrant lower left
		05   	U+258C 	▌ 			Left half block
		06   	U+259E 	▞ 			Quadrant upper right and lower left
		07   	U+259B 	▛ 			Quadrant upper left and upper right and lower left
		08   	U+2597 	▗ 			Quadrant lower right
		09   	U+259A 	▚ 			Quadrant upper left and lower right
		10   	U+2590 	▐ 			Right half block
		11   	U+259C 	▜ 			Quadrant upper left and upper right and lower right
		12   	U+2584 	▄ 			Lower half block
		13   	U+2599 	▙ 			Quadrant upper left and lower left and lower right
		14   	U+259F 	▟ 			Quadrant upper right and lower left and lower right
		15   	U+2588 	█ 			Full block

5. USAGE TIPS
	To obtain an image in plain PBM format for use with pbm2asciiblock, there are two easy methods:
	
	METHOD 1.
		If you have an image already, you can use the "convert" command to convert it to plain PBM format.
		e.g. On a Linux Ubuntu operating system
		
		Install the powerful convert command package with:
			$ sudo apt get install convert
		
		To convert an image called foo.gif into plain PBM format image called bar.pbm:
			$ convert -compress none foo.gif bar.pbm
		
		(The convert command is flexible in input image types (.png, jpg, gif, and many others)
		The "-compress none" creates a plain PBM format (type "P1") which is monochrome or 1-bit colour depth image.
		The PBM format is a plaintext file and can be read in a text editor.)
	
	METHOD 2.
		Use an image editing program, such as GIMP, to create and save the file as plain PBM format.
		e.g. On a Linux Ubuntu operating system
		
		Install the GIMP graphics manipulation package with:
			$ sudo apt get install gimp
		
		Run the program and create the required graphic as a Greyscale mode image. Images with around 10000 pixels (100x100) size may be too large
		for the computer memory to deal with (core dumping errors seen) when converting to blocks later, so around 10,000 pixels is a soft upper limit.
		
		From within GIMP, select File > Export As and select the PBM file type. When saving select ASCII output form rather than binary.
		This will produce a plain PBM file with a GIMP comment line in the file. The pbm2asciiblock will check for and ignore
		this GIMP comment if present, so you don't need to edit the .pbm in a text editor and can pass it directly for ASCII conversion.
		
		If you are using a different method to create the PBM file which creates comments elsewhere than the 2nd line
		of the PBM file then edit the PBM, using a text editor, and remove those comment lines prior to passing the image into pbm2asciiblock.


6. MISCELLANEOUS NOTES
	Old Nokia phones with monochrome screens had images of format .ngg, .nol, .nlm .NPM/.NLM/.OTB/.GMS/.NSL/.WBMP/
	Old phone image sizes are 84x48, 72x14, and 78x21 which is useful for a Google-image-size-exactly.. type of search.

	FULL BLOCK CHOICES
		Code 	Result 	Description
		U+2580 	▀ 	Upper half block
		U+2581 	▁ 	Lower one eighth block
		U+2582 	▂ 	Lower one quarter block
		U+2583 	▃ 	Lower three eighths block
		U+2584 	▄ 	Lower half block
		U+2585 	▅ 	Lower five eighths block
		U+2586 	▆ 	Lower three quarters block
		U+2587 	▇ 	Lower seven eighths block
		U+2588 	█ 	Full block
		U+2589 	▉ 	Left seven eighths block
		U+258A 	▊ 	Left three quarters block
		U+258B 	▋ 	Left five eighths block
		U+258C 	▌ 	Left half block
		U+258D 	▍ 	Left three eighths block
		U+258E 	▎ 	Left one quarter block
		U+258F 	▏ 	Left one eighth block
		U+2590 	▐ 	Right half block
		U+2591 	░ 	Light shade
		U+2592 	▒ 	Medium shade
		U+2593 	▓ 	Dark shade
		U+2594 	▔ 	Upper one eighth block
		U+2595 	▕ 	Right one eighth block
		U+2596 	▖ 	Quadrant lower left
		U+2597 	▗ 	Quadrant lower right
		U+2598 	▘ 	Quadrant upper left
		U+2599 	▙ 	Quadrant upper left and lower left and lower right
		U+259A 	▚ 	Quadrant upper left and lower right
		U+259B 	▛ 	Quadrant upper left and upper right and lower left
		U+259C 	▜ 	Quadrant upper left and upper right and lower right
		U+259D 	▝ 	Quadrant upper right
		U+259E 	▞ 	Quadrant upper right and lower left
		U+259F 	▟ 	Quadrant upper right and lower left and lower right

	https://en.wikipedia.org/wiki/Netpbm_format

	FURTHER POSSIBLE ENHANCEMENTS / EXERCISES FOR READERS
		- modify for arbitrary size images ( Memory handling? Current soft limit is around 10,000px)
		- objectify & prettyify code (This code is essentially a proof of concept.)
		- robustify treatment for arbitrary comment position
		- modify to accept also P4 "RAW PBM" binary files, or other image data types.
		- add figure & ground reversal feature, so output can be adapted for dark or light backgrounds. (Use NOT operator on PixelVal)

7. GALLERY OF EXAMPLES

████▀▜████████████████████▛▀████▛▀▀▀
███▛▐▝██▌▄▄▄▐▙████▛▘  ▝▜██▗▙▐███▌▛█▌
███▗█▙▐▗▖█▙█▝▀▀▀▜▛      ▜█ ▌▐███▌██▌
███▐█▟▝▝▘▙▙█▐▛▀▀▝▀▀▀▌ ▗▄▄▌▟█▖███▌██▌
▌▄▄▐██▐▜▌▙██▐▌██▛█▛▌▀▀▀▗▝▘▜█▌███▌█▛▌
▌██▐▟█▐█▌███▐▌▛▛█▛█▌██████▐█▌███▌██▌
▌██▐▟█▐█▌█▙█▐▌██▛█▛▌▙█▟█▙█▐█▌███▌▛█▌

████████████████████▛▜████████████████████
██████████████████▀▘ ▗█████ ▝▀▀▜████████▀▀
██████████████▛▜▀    ▘  ███▙▖             
▜▛█▜▛█▜▛█▀▄▞▘▗▝        ▟▛█▜▛█▜▛           
█▜▛█▜▛▙▀▄▞▘ ▄▘     ▝▛█▜▛█▜▛█▜▛▘ ▗▗▙       
▜▜▜▜▜██▀  ▗▝        ▝▜▛▛▛██▛▀▐ ▐ █▛    ▗ ▖
▛▛▛███▌▗▗▚▘    ▄ ▜▚   ▜▀█▀▘▗▖▗ ▗ ▝  ▐▜▜▛▛▛
▜▜████▚▘      ▟▛▙▟▜▜▙▄▛▜▜▖ ▗ ▝     ▞▛▙▜▞▛▜
▜█████▛ ▖    █▞▞▙▀▙▜▜▞▜▚▛▜▀▜▜▙ ▗▌ ▟▜▞▙▜▞▜▀
████▟▛▞▝    ▟▚▀▟▐▚▌▙▚▀▙▚▀▌▛▛▌▌▛▙▀▛▞▙▚▚▚▀▙▜
█▜█▟▙▀▀    ▜▚▚▜▐▀▌▟▝▌▜▖▜▚▀▞▞▟▝▙▐▚▀▞▄▚▜▝▙▚▚
▀▌▀▄ ▘     ▗▙▚▙▀▀▀▄▛▞▚▞▚▘▛▐▞▄▀▄▚▚▀▞▄▚▚▀▄▚▚
▘▝▖ ▘      ▝       ▝▚▚▝▞▚▘▙▗▞▐▗▚▝▞▞▗▚▘▙▗▚▖
                    ▐▝▞▐▗▚▗▘▞▖▚▝▞▖▚▘▞▖▚▝▖▞
              ▗▗▖▖▞▝▌▚▝▖▚▗▘▞▖▞▝▞▗▝▖▚▝▖▚▘▞▗
          ▗ ▚▀ ▚▗▗▝▖▘▞▗▝▖▖▚▗▗▝▖▝▖▘▞ ▚▝▗▝ ▚
 ▖▗▄▄▄▗▗▝▟▄▝▗▟▟▄▄▄▄▖▘▄▄▘▖▗▄▄ ▙▄ ▝▖▄▟▄▝ ▘▚ 
▘▗▐███▙  ██ ████████ ██▝▗██▘ ██ ▘▐███▌▘▝ ▖
▘ ▐█▛██▙▘██ ██    ██ ██▗██▘▝ ██ ▘██ ██▝ ▘ 
▘ ▐█▌▝██▙██ ██ ▗ ▘██ ██▜█▙ ▗ ██ ▐█▙▄▟█▌ ▗ 
 ▝▐█▌ ▝████ ██▄▄▄▄██ ██ ▜█▙  ██ ███████   
  ▐█▌  ▝███ ▜██████▛ ██  ▜█▙ ██▐█▌   ▐█▌  



                 ▗                        
                ▗▘▚                  ▞▖   
               ▗▘  ▚               ▗▀ ▝▚  
              ▗▀▖▞▖▞▚     ▞▖      ▄▘▗ ▗▗▚▖
             ▗▘ ▝ ▝  ▚  ▗▀ ▝▚   ▗▞ ▚▘▚▘▘ ▝
            ▗▘        ▚▗▘▚▀▚▘▚ ▄▘         
    ▞▖     ▗▘          ▚     ▄▀           
   ▞▖▞▖   ▗▘            ▚  ▄▀             
  ▞▝▝▝▝▖ ▗▘              ▚▀               
 ▞     ▝▄▘                ▚               
▞    ▄ ▗▘    ▄▄▄▄▄▄▄▖     ▄▖      ▗▄▄▄▄   
    ▟▄▙     ▐       ▐   ▗▟ ▐▄    ▗▘    ▚  
  ▞▀   ▀▚   ▐▗▀▀▀▀▀▚▐  ▞▘ ▚▘ ▀▖ ▗▘▗▛▀▀▙ ▚ 
 ▞  ▗▄▄  ▚  ▐▐▄▄▄▄▄▟▐ ▐▄▄▄▄▄▄▄▟ ▐ █▀▚▀▜▌▐ 
▐▄▀▛▘▝ ▀▛▜  ▞▟ ▞ ▘▝▖▛▖▛▗▄▄▄▄▄▄▝▌▐ ▌ ▖▖ ▌▐ 
▐  ▌ ▚▘ ▌▐  ▌▌ ▚▝▞▗▘▌▌▐▘▗▘▖▗▝▖▜▘▐ ▌ ▞▖ ▌▐ 
▝▖ ▝▄▘▚▞ ▟  ▚▚  ▀▝▘ ▚▘▐ ▝▖▗▖▗▘▐ ▐ █▀ ▝▜▌▐ 
▗▀▚▖ ▄▖ ▞ ▚  ▝▄ ▗▄ ▗▘  ▚ ▝▘▝▘ ▞ ▝▖▝▚▄▄▀ ▞ 
▙▖ ▝▄▄▄▀  ▟▖ ▗▘▀▄▄▞▀▖  ▞▀▄▝▘▄▀▚  ▐▖ ▐  ▟  
▌▐   ▗▌  ▐ ▌▗▙▖▖▖▌▗▗▟▖▗▚  ▜▛  ▞▖ ▌▝▀▜▀▀ ▌ 
▜▘   ▗▌   ▜▘▐ ▌▙▌▌▟▐ ▌▌ ▌ ▗▌ ▐ ▐▗▀▌ ▐  ▛▚ 
 ▙▄▄▄▄▙▄▄▄▌ ▝▀▄▄▄▙▄▄▀▘▝▜▄▄▄▙▄▄▛▘▝▄▘▄▟▄▖▚▞ 
 █████████▌   ██████   ▙▄▄▄▙▄▄▟  ▗█▙▟▄█▙  


       ▗▄                                 
▜██▘   ▐█                                 
 █▌                                       
 █▌   ▗▄█ ▄▟▙▟█▙ ▗▟▌ ▄█▌▐██ ▐█ ▗███▄      
 █▌    ▜█  █▛ ▜█  █▌ ▝█▌ ▐█▖▟▘ █████▖     
 █▌    ▐█  █▌ ▐█  █▌  █▌  ▜█▌  ▛▀▛▀█▌     
 █▌  ▗ ▐█  █▌ ▐█  █▌  █▌  ▐█▙  ▌▙▙▌█▌     
 █▌  █ ▐█  █▌ ▐█  █▙ ▗█▌ ▗▛▝█▖ █▘ ▀██     
▄█████▗▟█▖▄█▙▖▟█▙ ▐██▀█▙▗█▙ ██▖▙▚▄▘██     
                              ▗▛▙▄▞▜█▌    
                     ▄▄▄▄▄▄▄  ▟     ██▖   
         ▄▄▄▄▄▟█████████████▀▟█     ▜██   
  ▄█████████████████▀▀▀▘     █▘     ▝██▌  
 ▟███████████▛▀▀▘           ▐█       ███  
 ████████▀▀                 █▌       ███  
 █████▀                     █▌       ███  
 ▀█▀▘                      ▐ ▜▖     ▞▜██▖ 
                         ▗▀▘  █▖    ▌ ▀▘▌ 
                         ▝▖   ▝▛   ▗▟   ▝▚
                         ▗▘    ▚▄▄▄██   ▄▘
                          ▀▚▄▖ ▟▛▀▀▀█ ▗▀  
                             ▝▀▘    ▝▀▘   
    
      ▟▌                                  
     ▟▌      ▐▙  ▗▄▖ ▗  ▗▄▖               
    ▗██████▖  █▖ ▌ ▐ ▌  ▌ ▝               
    ▐█▛█████▙██▌ ▌ ▐ ▛  ▌  ▗▀▚▐ ▐▐▘▞▚▗▀▚  
    ▐▛▐▌ ██████▌ ▌ ▐ ▌  ▌  ▐ ▐▐ ▐▐ ▝▖▐▀▀  
    ▐▗▐  ▐████▛  ▚▄▞ ▌  ▚▄▞▝▄▞▝▄▜▐ ▚▞▝▄▞  
    ▟███ ████▛                            
   ▐███▌▄████                             
  ▀▐█████████       ▌▗  ▐▀▀▖              
 ▜▖▌▀███████▛       ▌▐▖ ▐  ▌▗ ▗▗▗▖ ▄      
▄▗█▄▄▞▜████▛        ▌▐  ▐▀▀▖▐ ▐▐▘▐▝▖▘     
▝▀ ██▙▐████▙        ▌▐  ▐  ▌▐ ▟▐ ▐▗▝▖     
   █████████        ▘ ▘ ▝  ▘ ▀▝▝ ▝ ▀      
   ▝▀███████                              
     ▐██████      ▐▙ █    ▗▖▐▛▜▖▗▛▜▖▐▛▜▖  
     ▐██████      █▙▐▌ ▄▄ █▖█ █ █   █ ▐▌  
     ▝█████▙     ▐▛▙█ █▄█▐▌▐▛▜▖ ▀▜▖▐▌ █   
      ██████▌    █ █▌▐▌▗▖█ █ █ ▄ █ █ ▟▘   
      █████▛█▖  ▝▘ ▀ ▝▀▘ ▀▝▀▀  ▀▀ ▝▀▀     
 ▟▀████████▌▝██▙▄                         
 ▀▜█ ▗██████████▀▜█▖                      
   ▝▚██████████▘▟ ▗█▙▖                    
      ▝▀▀▀▀▀▀▀▗██████▛                    
              ▀██▀▀▀▀                     

             ▗▄            ▗▄             
          ▗▟█████▄      ▗▟█████▄          
         ▗█████████▖   ▟████████▙         
        ▗███▛▀▀▀▜███▖ ▟███▛▀▀▀███▙        
        ▟██▘     ▀███▟██▛▘     ▜██▌       
       ▗██▌       ▝█████   ▟▙   ███       
       ▐██▘ ▗▄▄▄▖  ▜███▘  ▄██▄  ▐██       
       ▐██  ▐███▌  ▗███   ████  ▐██       
       ▐██▖        ▟███▌   ██   ▟██       
        ██▙       ▟█████▖  ▀▀  ▗██▛       
        ▜██▙     ▟██▛▝███▄    ▗███▘       
         ████▄▄▟███▛  ▝████▄▄▟███▛        
         ▝▜███████▛    ▝████████▀         
           ▀▜███▛▘       ▀▜███▀▘          
                                          
         ▗▖ ▗▄▄ ▄▄▖▗▄ ▄▗▄▄▖▄▖▗▖▗▄▖        
         ██ █▛█▌█▀█▐█▐█▝▜▛▘█▙▐▌█▀█        
        ▗▌▐▖█▙█▘█ █▐█▐█ ▐▌ ███▌█ █        
        ▐██▌█▛█ █▄█▝█▟█▗▟▙▖█▛█▌█▄█        
        ▀▘▝▀▀▘▀▘▀▀▘ ▀▀▘▝▀▀▘▀▘▀▘▝▀▘        
                                          
 
▙▌▞▖▛▖▜▘▞▖▖▖▞▖▞▖▗▀▚▗▗▗▚▗▚ ▌ ▌▐  ▌ ▜▘▌▌▞▖▞▖
▌▌▛▌▛▖▐ ▌▌▞▖▌▌▗▘▐▝▐▗▚▐▐▐▐ ▌▌▌▐▝▘▌ ▐ ▀▌▌▌▌▌
▘▘▘▘▘▘▀▘▝   ▝ ▀▘ ▀▘   ▘ ▘ ▝▝ ▝  ▘ ▝  ▘▝ ▝ 
                                          
                       ▞▖                 
                      ▞ ▝▖                
                     ▞   ▝▖               
            ▞█▛▖    ▞     ▝▖              
            ▛▗▌▌   ▞       ▝▖             
            ▌▗ ▌  ▞         ▝▖            
          ▖ ▝▀▀  ▞        ▗▄ ▐▄           
         ▞▝▖    ▞        ▗▘▗▙▙▝▙          
        ▞  ▝▖  ▞         ▝▗▘▐ ▚▝▖         
   ▄▄▄▄▟▄▄▖ ▝▖▞   ▗▄ ▗▄   ▝ ▐ ▝ ▝▖        
   ▌    ▝▟▌  ▝▖  ▗▘▗▙▙ ▚    ▐    ▝▖       
   ▌    ▝▟▌▗▟█▟▖ ▝▗▘▐ ▚▝    ▐     ▝▖      
   ▜▀▀▀▀▛█▘▟▜▀▛▞▖ ▝ ▐ ▝     ▐      ▝▖     
   ▟    ▞█ ▜▝▘▗▘▝▖  ▐       ▐       ▝▖    
  ▞▝▄▄▄▄▟▛ ▟███▖ ▝▖ ▐       ▐        ▝▖   
 ▞ ▐    ▞█ ██▟▟█  ▝▖▐       ▐         ▝▖  
▞  ▐    ▞█ ▗█▌█▖   ▝▟       ▐          ▝▖ 
▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀
██████████████████████████████████████████
▙▙▙▙▙▙▙▙▙▙▙▙▙▙▙▙▙▙▙▙▙▙▙▙▙▙▙▙▙▙▙▙▙▙▙▙▙▙▙▙▙▙


                         █████████████████
                        ▐████▜▀███▛▀▄▚▜███
   ▗▖   ▄▖▗▄ ▗▄▟▖  ▄▄▖   ██▟▀▛▛▙▙▚▄▘▝▖▚▐██
    ▞▘ ▐█ ██ █▛▜▛ ▗██▖  ▝██▄▛▜▟▐▚▄▞▞▚▀▞▗▛█
    █▙ █▛ █▌▐█▙   ▟██▌  ▗█▘▘▝▜▀▘▌▀▝▘▝▝▀▝ █
    ▐█▐█▘ █▌ ▜██▖ █▌▜█  ▗█▘ ▝ ▖▘ ▖▗▗▘▘  ▗█
    ▐██▛ ▐█▘  ▝█▌▟█▙▟█   █▄▄▄▗▖▄▖▄▐▖▄▗▐▗▖█
     ██▌ ▟█ █▄██▘█▛▀▜█▘ ▐█▌▛▙▙▀▙▟▚▌▐▘▞▚▘▄█
     ▝▀  ▝▀ ▀▀▀ ▝▀   ▀▘  ██▙▛▜▄▛▟▞▝▞▖▚▐▞██
                        ▐███▙▛▙▙██▙▚▘▞▙███
                         █████████████████
  ▗  ▗ ▗▖▄▗▗▖▄▖                           
  ▞▗▖▚▐▚▄██▜██▌                           
  ▐▝▄▝▘▞▟▐▟▙█▙▌                           
  ▗▘▗▘▚▀▐▟▜█▜█▌                           
  ▞▝▗▀▞▐▜▞▛▛▛█▌   ▟▄▙▄         ▗▙▄▄     ▗▖
  ▘  ▖▄ ▄▖▘▄▄▝▌   █▛▀█▌▄▄▖▗▄ ▗▄▐▛▝▜▌▗▄▖ ▐▌
   ▝▝▝▗▝▖▐▝▝▌▌▌  ▗█▖▟█▝▀▜█▐█ ▟▌█▌▗█▌▀▘█▖█▘
  ▟▜▌▝▝▀▞▝▀▞▐▝▘  ▐██▛▘▟▛▜█▝█▟▛ █▛▛▘▗▞▀█ █ 
  ▟▜▌▚▞▖▝▌▌▞▚▀▖  ▟▌  ▐█▖▟▙ ██▘▗█   █▌▄█▗▛ 
  ▜▜▄▄▟▄▙▗▄▄▙▄▌  ▝▘   ▀▀▀▘ █▛ ▝▘   ▝▀▘▘ ▘ 
  ▟█▛█▛███████▌           ▐█              
  █▙▟█▙███████▌                           
  ████████████▌                           


█████████████████▜▞▛██████▜▜▚▝▜▜█▙▜▜█████▟
███████████████▟▙█▟▀▙▛▛██▛▙▜▚ ▞▜▜▚██▟███▙█
█████████████████▙▙▛▞▟▚▜▜█▜▌█▗▞▙█▛█▟████▜▟
███████████████████▟▐▝▞▞▞▞▛████████▟█████▟
████████████████████▌▖    ▛████████▟██████
██████████████▀▖▞▞██▟▗   ▝▝▖▘ ▚▚▞█▛▟██████
██████████████▙▟▟▟███▄   ▐▐▐▞▌▖▐▐█▀▜█▜████
█████████████████████▄    ▜██████▌ ██████▚
███████████████▜▀▜███▖     ▝▜███▀  ▐▙▚▝▝▗▚
█████████▙▚▞▗▗▗▘▜▜███▌        ▘    ▟█▌ ▘  
█████████▟▞▞▗▘▞▐▀███▛▞             ▐█▟ ▝ ▝
█████████▟▞▞▗▘▞▞▟████▖             ▜█▟  ▗▗
█████████▙▌▌▚▝▗▐▟███▙              ▜█▙▙▚▗▐
█████████▙▜▐▗▝▖█████▟             ▐█████▞█
███▛▞█████▚▌▖▖▞▜█████▄            ████▟█▛█
███▛▟▟████▚▞▖▖▞▌████▛▘           ▗███▞██▌▚
████▜▟███▛▙▚▚▚▚▚▙▙▚▘             ▟██▙▚█▜▚▘
████▙█████▙▚▙▛▟▙▙▙▙▄▖▖           ▟█████▚▚▚
████▙█████▟▚▚▐█████████▟▄▖▖     ▗█████▌▌▘ 
█████▟█████▟▐▐██████▛▛▌▚▚▀      █████▘  ▖ 
███████████▞▄▜██████▟▐▝▖▘      ▐████▀ ▗   
█████████████▜▟▜▜▀▚ ▘▘▘        ▛▀       ▝ 
▝▀▜█▛▜███████▜▟▌▌▞            ▟     ▘  ▖ ▖
▟▟▟▄█▙████████▟▟▗▖▖          ▝       ▝  ▖▖


                ▄     ▗▟█████▄  ▄█████▙▖  
                ▜▙    ██▛▀▝▀▀█▙▟█▀▀▀▀▀██  
               █▙█▙   █▙ ▗▄  ▝██▘  ▄▖ ▜█  
              █▌▝▀█▙  ▜█  ▀█▄ ██ ▄█▀  █▛  
             ▞█▙▖ ▗█  ▝█▌  ▝▜▙▌▐▟▛▘  ▐█▘  
            ▗█ ▜█▖ ▘   ▜█▌  ▗▌  ▐▖  ▐█▛   
            ▝█▙ ▝       ▜▛▙▄▛▗▄▄▖▜▙▟█▛    
           ▟█▙▀█        ▟█▀▜█▀  ▀▟▀▜▟▙    
           █▟▌▙        ▐█▘▗▛▜    █▙ ▝▛▌   
        ▖▗▄▞███        ▛▌▄▛▄▟█▙▄█▙▟▙▖██   
       ▝██▛██▝        ▗▛█▚▛▘▝▜▖▐▀ ▝▜██▐   
        ▝▜█▄█▘        █▟▌▟    ▙▟    ▙▟█▜  
       ▗█▙▛█▛        ▐█ ▛▌    ██    ▐▌▝▛▌ 
       ██▝█▖         ▐▌ ▛▌   ▗▌▐▖   ▟▌ ▌▌ 
      ▄▞▜██▘         ▐▙ ▌▜▖ ▗█▄▄█▖ ▗▌█ ▛▌ 
     ▐█▟█▞█▙         ▐█▟▘ ▀▀▜▛▘▝▜▛▀▀▄▟▟▚▌ 
     ▖▜▛▟▛ ▀ █▗       ▙▜▀▜▄ ▛    ▜ ▟▘▐▌█  
    ██▙▞▛▘  ▄▄▜█▖     ▐▐  ▝▌▌    ▐▟▘  ▙▌  
 ▗▄ █▐▛█▘  ▐█▜▙▝█▙    ▝█▖  ▜▜    █▌  ▐█▘  
▗███ ▐█▛   ▜█▟█  ▘     █▙  ▐▝▜▄▄▟▜▌  ▟▛   
▐█▄██▙▛     ▝█▙▖       ▝██▄▟▗▄▟▙▄▞▙▄██▘   
 ▝██▛▀▘       ▀█        ▝▜▄ ▛▘   █ ▄▛     
   ▀█▖                    ▝▜█▄ ▗▟▚▛▘      
    ▝                       ▀████▀        


*/

//Includes
#include <istream>
#include <iostream>
#include <fstream>
#include <string>

//Debug
//#define DEBUG_ON //Uncomment the start of this line to write out extra info during code execution.

using namespace std;

int main (int argc, char* argv[])
{
 	//Check the correct arguments were used
 	if (argc < 2)
 	{
 		//Give usage instructions:
 		cerr << "Usage: "<< argv[0] << " inputFileName.pbm\n";
 		cerr << "Output may be directed to a file as required:\n";
 		cerr << "e.g. "<< argv[0] << " inputFileName.pbm > output.txt\n\n";
 		return 1;
 	}
 	// argv[1] is the filename to read the image data from

 	//Setup constants
	const char* FILETYPE = "P1";             // OFFSET - UNICODE  CHAR  DESCRIPTION
	const char* ASCII_BLOCKS [16] = {"\u0020",  // 00 - U+0020    " "  Space, i.e. Empty block
									 "\u2598",  // 01 - U+2598 	▘ 	Quadrant upper left
									 "\u259D",  // 02 - U+259D 	▝ 	Quadrant upper right
									 "\u2580",  // 03 - U+2580 	▀ 	Upper half block
									 "\u2596",  // 04 - U+2596 	▖ 	Quadrant lower left
									 "\u258C",  // 05 - U+258C 	▌ 	Left half block
									 "\u259E",  // 06 - U+259E 	▞ 	Quadrant upper right and lower left
									 "\u259B",  // 07 - U+259B 	▛ 	Quadrant upper left and upper right and lower left
									 "\u2597",  // 08 - U+2597 	▗ 	Quadrant lower right
									 "\u259A",  // 09 - U+259A 	▚ 	Quadrant upper left and lower right
									 "\u2590",  // 10 - U+2590 	▐ 	Right half block
									 "\u259C",  // 11 - U+259C 	▜ 	Quadrant upper left and upper right and lower right
									 "\u2584",  // 12 - U+2584 	▄ 	Lower half block
									 "\u2599",  // 13 - U+2599 	▙ 	Quadrant upper left and lower left and lower right
									 "\u259F",  // 14 - U+259F 	▟ 	Quadrant upper right and lower left and lower right
									 "\u2588"   // 15 - U+2588 	█ 	Full block
									  };

#ifdef DEBUG_ON
	cout << "Test of block output: \n";		
	for ( int i=0 ; i < 16 ; i++)
	{
		cout << i << ": " << ASCII_BLOCKS[i] <<"\n";
	}
#endif

		
	string lineRead;//Declare variable for reading lines from file
	unsigned int ImgHeight, ImgWidth; //Declare image height & width variables

	//Open file for reading
	ifstream inputFile (argv[1], ios::in); //Set filename specified in command line as input stream
	if (inputFile.is_open()) //If file opened successfully...
	{
		cout << "File opened for reading....\n";

		//File operations here
		getline (inputFile,lineRead); //Read first line of filetype

		//Confirm the file is of the expected PBM image type
		cout << "Expected PBM type: " << FILETYPE <<"\nReceived PBM type: " << lineRead <<"\n";
		if (lineRead == FILETYPE) 
		{
			cout << "Correct filetype detected.\n";
		}
		else 
		{
			cerr << "Incorrect filetype detected.\n";
			return 1; //Abort program
		}

		//cout << lineRead << "\n"; //output line read from file.

		//Check if comment line before image data
		//inputFile.ignore(1000,'\n'); //flush buffer from reading image width and following newline
		if( inputFile.peek() == '#') //peek returns an int. Compare with ASCII value for "#" - a comment indicator.
		{
			cout << "Comment line detected:\n";
			getline (inputFile,lineRead); //Read comment line
			cout << lineRead <<"\n";	
		}

		inputFile >> ImgWidth >> ImgHeight; //read Image dimensions

		cout << "Image height is: " << ImgHeight << " pixels.\n";
		cout << "Image width  is: " << ImgWidth << " pixels.\n";




		if (ImgWidth > 140) //Warn if image is wider than 140px = 70 blocks, as it won't fit on single line in forum comment.
		{
			cout << "WARNING: Output will be wider than 70chars, and could get line wrapped if used as a forum comment.\n";
		}

		unsigned int BitMap [ImgHeight] [ImgWidth]; //Set the array to hold the image data
		char a;

		for (int i=0; i < ImgHeight; i++)
		{
			for (int j=0; j < ImgWidth; j++)
			{
				//Read space separated plain PBM
				inputFile >> a;
				BitMap [i] [j] = a-'0';//convert char to int
			}
		}

		#ifdef DEBUG_ON
		cout << "Test of reading image: \n";
		for (int i=0; i < ImgHeight; i++)
		{
			for (int j=0; j < ImgWidth; j++)
			{
				cout << BitMap [i] [j] << " ";
			}
			cout << "\n";
		}
		#endif
		
		cout << "Finshed reading file....Now closing file.\n";
		inputFile.close();



		int AscHeight = int ((ImgHeight+1) / 2);//Set the ASCII image dimensions to half the PBM image, as 1 ASCII block = 2x2 pixels...
		int AscWidth = int ((ImgWidth+1) / 2);//..and if the Image dimension is an odd number add a 1 pixel padding before converting to blocks, since we can't use half ASCII blocks.
		//const char* AscMap [AscHeight] [AscWidth]; 
		unsigned int AscVal, PixelVal[4]; //PixelVal is a 2x2 array to hold values of each pixel in the 2x2 pixel region (which is 1, or 0 from the 1-bit PBM image data).
		
		cout << "ASCII image height is: " << AscHeight << " characters.\n";
		cout << "ASCII image width  is: " << AscWidth << " characters.\n";

		for (int i=0; i < AscHeight; i++)
		{
			for (int j=0; j < AscWidth; j++)
			{
				//Set PixelVal array to values in BitMap of 2x2 block region
				PixelVal [0] = BitMap [i*2] [j*2];
				PixelVal [1] = BitMap [i*2] [j*2+1];
				PixelVal [2] = BitMap [i*2+1] [j*2];
				PixelVal [3] = BitMap [i*2+1] [j*2+1];
	
				//Calculate the value of the block
				AscVal = PixelVal [0] + 2*PixelVal [1] + 4*PixelVal [2] + 8*PixelVal [3];
	
				//Set the ASCII block according to the value
				cout << ASCII_BLOCKS [AscVal]; //Output character
		
				//AscMap [i] [j] = ASCII_BLOCKS [AscVal]; //Store values in array <- No longer needed if writing immediately to std out.
			}
			cout << "\n";//Output newline at end of each row
		}

	}
	else 
	{
		cerr << "Unable to open file: " << argv[1] <<"\n";
		cerr << "Check the file exists, its access permissions, and whether it is locked from reading.\n";
		return 1;
	}

  cout << "Operation completed successfully.\n";
  return 0;
}