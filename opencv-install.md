# How To - Installing OpenCV for vcl use

Library **vlc** clearly takes benefit of external library **OpenCV** as an 
underlying layer of its core code. You will have to install **OpenCV** on 
your own machine to be able to use **vcl** in your code as well as to be 
able to run your final applications on your machines.

This intallation document aims at helping you to do so. It is split in two 
main parts. The first one relates to the installation of the OpenCV library 
on your operating system platform. The second one relates to the setting of 
your projects configurations to get access to any **OpenCV** goodies that 
are mandatory for **vcl** to compile and run.

Notice: At first, we document Windows platforms usage. We know that Linuxians 
are great fellows. They get used to use external software and they know do 
how to install them according to their favorite linux platforms (Debian, 
Red Hat, Ubuntu, ...) As soon as we will have tried to set these exotic 
environments by our side, we will provide the proper explanations here. 
Meanwhile, Linuxians will have to do the job by themselves. For sure they 
know how to.


## 0. Intro - OpenCV version and c++ version used for vcl

By February 2022 we are using **OpenCV** in its latest and stable version 
**4.5.5** - see:
- [https://opencv.org](https://opencv.org/) for an overview of OpenCV,
- [https://docs.opencv.org/4.5.5](https://docs.opencv.org/4.5.5/) to get 
  access to the latest version of its documentation, and
- [https://github.com/opencv/opencv](https://github.com/opencv/opencv) to 
  get access to its whole c++ code (preferably branch 4.x for current 
  version of **vcl**).
  
By February 2002, **vcl** is under draft development - release v0.0) and 
is implemented using the latest stable version of c++: C++20. We provide 
advices for the setting of your projects configuration.

Notice : For the developement of library **vcl**, we are currently using 
Microsoft Visual Studio Community 2022 (64-bit) in its Version 17.0.5 
(*copyright 2021 Microsoft Corporation*). We strongly encourage students, 
families and Open Source devs who are developping on Windows to use this 
framework on their favorite platforms. This release of this IDE takes big 
benefits from the Professional version of this IDE and is released for free 
for those people and type of activities. If your developements are 
profesionnal or for business purpose ones, then you **should** get a pro 
licence of Microsoft Visual Studio 2022 IDE.

Any other IDE will fit also, either on Windows or on any other platform. 
The configuration of the developped projects in there is nevertheless left 
to the responibility of their users. 




## 1. Intalling OpenCV on your platform

It is mandatory to install **OpenCV** on your Windows platform to be able 
to use **vcl**, since **vcl** using **OpenCV** as an underlying layer. So,
we try to explain here how to do, as far as we can.


### Linux

As stated above, Linuxians are great fellows. They know "how to" far better 
than we can explain for their favorite platform(s).

We will finally use a Linux platform to develop **vcl**. Finally will we. 
One day. By this day, we will be able to provide documentation about this.  
This is not yet that day.


### Windows

We are developping **vcl** under Windows 10, using **OpenCV 4.5.5**.

A very good document for the installation of **OpenCV** can be found at [https://docs.opencv.org/4.5.5/d3/d52/tutorial_windows_install.html#tutorial_windows_install_path](https://docs.opencv.org/4.5.5/d3/d52/tutorial_windows_install.html#tutorial_windows_install_path)
(from Bernát Gábor). There, you'll get explanations for older versions of 
**OpenCV**, but they still remain valid for the latest one!

Nevertheless, here below are the three simple steps to take for installing
**OpenCV 4.5.5** on **Windows platforms**:

**1.** Download Windows installer from [https://opencv.org/releases](https://opencv.org/releases/) 
(direct link for this download: [https://sourceforge.net/projects/opencvlibrary/files/4.5.5/opencv-4.5.5-vc14_vc15.exe/download](https://sourceforge.net/projects/opencvlibrary/files/4.5.5/opencv-4.5.5-vc14_vc15.exe/download))

**2.** The donwloaded file is a self-extracting archive. Double click on it 
then in the editable text field with title `Extract to:`, put the destination 
folder of your choice. `C:\` or `D:\` could be an excellent choice. We have 
decided to extract it into a specific folder on our platform that we dedicate 
to external libraries: `D:\Libs`.  
Once extraction will have completed, you'll get a new folder named `opencv` 
created and filled in the destination folder of your choice - for instance, 
resp. `C:\opencv`, `D:\opencv` or `D:\Libs\opencv`.

**3.** Add the next environment variable to the systme path:  
`OPENCV_DIR`, to be set resp. to `C:\opencv\Build\x64\vc15`,  
`D:\opencv\Build\x64\vc15` or `D:\Libs\opencv\Build\x64\vc15` according to 
the choice you will have done for the installation of all the **OpenCV** 
stuff at step **2.**  
**Caution**: `x64` stands for 64-bits platforms, which is our case. You may 
be using a 32-bits platform. Replace then `x64` with `x86`.  
Meanwhile, `vc15` stands for the latest releases of Microsoft Visual Studio 
and is valid for Microsoft VS 2022. It will be your responsability to check 
if this is valid also for Microsoft VS 2019 if you wish to use this older 
version. If not, try replacing `vc15` with `vc14`. You nevertheless are 
strongly encouraged to use the latest versions of tools, as long as you can.



## 2. Configuring your projects for using OpenCV

To be able either to compile **vcl** by your side, or to be able to use 
OpenCV code within any development of your own, you must properly set the 
configuration of your compiling and linking environment. We suggest here 
easy ways to accomplish this.


### 2.1. Linux
("*bis repetita*" once said one of my oldest Roman friends, far away from 
now)

As stated above, Linuxians are great fellows. They know "how to" far better 
than we can explain for their favorite platform(s).

We will finally use a Linux platform to develop **vcl**. Finally will we. 
One day. By this day, we will be able to provide documentation about this.  
This is not yet that day.

Meanwhile, below explanations for Windowsians should help any alien platform 
developper to get what must be configured and how it should be for 
compilation and linkage stuff to properly operate.  

"*Bon courage !*"  
(well, indeed, I'm French as my poor English should have already suggested)


### 2.2. Windows

Unfortunately, project configuration is strongly dependent on the IDE tool 
you use.

As mentionned formerly, we are developping **vcl** within the frame of 
Microsoft Visual Studio 2022 (Community version for its freeness and due to 
the Open Source nature of project **vcl**).

Should you use any other IDE (e.g. Eclipse, Visual Studio Code, CodeBlock, 
etc.) you might get inspired by the following explanations, even if they 
are specific to Visual Studio 2022.

Here again, a very good text tutorial is available here: 
[https://docs.opencv.org/4.5.5/dd/d6e/tutorial_windows_visual_studio_opencv.html](https://docs.opencv.org/4.5.5/dd/d6e/tutorial_windows_visual_studio_opencv.html)
(from Bernát Gábor also). There, you'll get explanations for older versions 
of **OpenCV**, but they still remain valid for the latest one!

Let's explain shortly the different actions you have to take for taking full 
benefit of OpenCV in your developement environment.


#### 2.2.a Compiler - Set Additional Include Directories
Remember: during step *1. Installing OpenCV on your platform* you 
have set an environment variable, `OPENCV_DIR`. All the **OpenCV** includes 
are now contained in a folder whose relative path is `$(OPENCV_DIR)\..\..\include` 
and absolute path is resp. `C:\opencv\build\include`,`D:\opencv\build\include` 
or `D:\Libs\opencv\build\include` according to your initial choice for the 
installing of the whole **OpenCV** stuff on your machine.

So, you can now add either this relative path or the correct absolute path 
to the additional include directories in your project configuration. To do 
this with MVS 2022, right click on your project name in the *Solution Explorer* 
panel, select the very last item in the popped-up menu list (`Properties`). In 
the modal window that appears, unroll *Confiduration Properties*, then 
*C/C++* and click on *General*. You will then be able to add the relative as 
well as the absolute path to the **OpenCV** includes at the very first line*
shown in there : *Additional Include Directories*.  
Notice: set this for *All Configurations* and for the related platform (i.e. 
either *x64* or *Win32*).  
The relative path **should** work there. If compilations errors occurs due 
to not found includes, try to set there the absolute path. Things will be 
less general in your configuration file, but your project will be correctly 
set and compilation will be ok..


#### 2.2.b Linker - Add OpenCV global library
Ok, now that we have set configuration for the C++ compiler, let's set it 
also for the linker.

Within the **same modal window**, unroll the item *Linker* and click on 
*Input*. There, the window shows at topmost line of configs setting the 
*Additional Dependencies*. These are the mandatory external libraries that 
must be linked with your project for calls to **OpenCV** classes, methods 
and functions to properly operate.

There, you will set
- for Configuration *Release* and platform *x64*:  
`C:\opencv\build\x64\vc15\lib\opencv_world455.lib`, 
`D:\opencv\build\x64\vc15\lib\opencv_world455.lib` or 
`D:\Libs\opencv\build\x64\vc15\lib\opencv_world455.lib` according to the 
folder in which you have install the whole **openCV** stuff at step
*1. Installing OpenCV on your platform*;
- and for Configuration *Debug* and platform *x64*:  
`C:\opencv\build\x64\vc15\lib\opencv_world455d.lib`, 
`D:\opencv\build\x64\vc15\lib\opencv_world455d.lib` or 
`D:\Libs\opencv\build\x64\vc15\lib\opencv_world455d.lib` according to the 
folder in which you have install the whole **openCV** stuff at step
*1. Installing OpenCV on your platform*.

Do the same thing by replacing `x64` by `x86` for *Win32* platforms, as long 
as you will have installed the 32-bits build of **OpenCV** - which is 
currently not our case.


## 999. Then, you're done!
You should now be able to compile **vcl** by your side, as well as compile 
and run the small test code provided at section **Test it!** near the end 
of page 
[https://docs.opencv.org/4.5.5/dd/d6e/tutorial_windows_visual_studio_opencv.html](https://docs.opencv.org/4.5.5/dd/d6e/tutorial_windows_visual_studio_opencv.html).

Well, the creation of this test project is left to you as an interesting 
exercise - whatever your platform and IDE are.

