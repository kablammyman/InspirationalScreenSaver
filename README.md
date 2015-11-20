# InspirationalScreenSaver

This is a picture slide show screen saver. I use the CFGLib I created to set the configuration options at start up. This also used allegro4 with the jpegAlleg extension. The current version was being set up to use SQLite3, but it does nothing with the lib yet...this is to work with SmartCatalogue. It will only compile with visual studio 2010 (or a more recent version of VS that uses visual studio's 2010 compiler set in the project options)

This program has a very long history for me. Originally, I used the slide show screen saver that came with windows XP. Once I realized only a small subset of my images were able to be used, I found a similar program that could display all of my images (its called jpegSaver, its a great app). The issue with that program was that my photo collection was growing all the time, and having to re-scan the photo directory for caching was a time consuming process. I made an app to interface with that program to do this for me, then it would launch the screen saver when my app was done. My app was configurable…so I could only load a random directory or randomly pick X directories from a list. Eventually that jpegSavwe was updated and changed the way it worked (it went from using text files to a database) and then it stopped being updated at all. What that meant is that couldn’t use my app to manipulate jpegSaver.


That’s when I decided to make my own screen saver…one that just reads from a directory and can select what images to display on the fly, even if new images are added while the screen saver is running. This current version in the 2nd iteration of the screen saver (and 3rd of the app if you include the time it used to just interface with text files from jpegSaver) With the first screen saver, I was able to delete images or whole directory of images during the slide show with the press of a key on the keyboard. It also had a timer…a primitive version of the stop watch project. The code was turning into spaghetti, since it wasn’t meant to do more than show some images, but i was adding things all the time like an image shown history. Since the code became a mess, and I had bigger ideas that I wanted to try, I rewrote it to make it more modular…and this re-write is what is on github.


The latest version is feature complete with the previous version, but I haven’t added the new features I wanted yet. I did fix some older issues, and made things much more efficient, but adding the new transitions and image selection techniques hasn’t happened yet. Maybe one day… 

Future plans:

New and interesting screen transitions

New and interesting image selection techniques

Add the stop watch timer to the app so I can change the timer interval without a restart

Interact with SmartCatalogue

Support full screen and window display (hopefully resizable windows with fully working windows controls)

Being able to use my “super clever” algo to prevent showing repeat images for directories that have more than 128 images
