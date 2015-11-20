# InspirationalScreenSaver

This is a picture slide show screen saver. I use the CFGLib I created to set the configuration options at start up. This program has a very long history for me. Originally, I used the slide show screen saver that came with windows XP. Once I realized only a small subset of my images were able to be used, I found a similar program that could use all of my images. The issue with that program was that my photo collection was growing all the time, and having to re-scan the photo directory for caching was a time consuming process. I made an app to interface with that program to do this for me, then to launce the program. My app was configurable…so I could only load a random directory or randomly pick X directories from a list. Eventually that program was updated and changed the way it worked (it went from using text files to a database) that means I couldn’t use my app to do what I wanted.


That’s when I decided to make my own screen saver…once that just reads from a directory and can select what images to display on the fly, even if new images are added while the screen saver is running. This current version in the 2nd iteration of the screen saver (and 3rd of the app if you include the time it used to just interface with text files from that other screen saver) With the first screen saver, it was able to delete images or whole directory of images during the slide show with the press of a key on the keyboard. It also had a timer…a primitive version of the stop watch project. The code was turning into spaghetti, since it wasn’t meant to do more than show some images. Since the code became a mess, and I had bigger ideas that I wanted to try, I rewrote it to make it more modular…and this re-write is what is on github.


The latest version is feature complete with the previous version, but I haven’t added the new features I wanted yet. I did fix some older issues, and made things much more efficient, but adding the new transitions and image selection techniques hasn’t happened yet. Maybe one day… 

Future plans:

New and interesting screen transitions

New and interesting image selection techniques

Add the stop watch timer to the app so I can change the timer interval without a restart

Interact with Smart Catalogue

Support full screen and window display (hopefully resizable windows with fully working windows controls)

Being able to use my “super clever” algo to prevent showing repeat images for directories that have more than 128 images
