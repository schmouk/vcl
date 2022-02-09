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
(from Bernát Gábor). There, you'll get explanations for older versions of OpenCV, but they still 
remain valid for the latest one!

Nevertheless, here below are the two simple steps to take for installing
**OpenCV 4.5.5** on **Windows platforms**:

**1.** Download Windows installer from [https://opencv.org/releases](https://opencv.org/releases/) 
(direct link for this download: [https://sourceforge.net/projects/opencvlibrary/files/4.5.5/opencv-4.5.5-vc14_vc15.exe/download](https://sourceforge.net/projects/opencvlibrary/files/4.5.5/opencv-4.5.5-vc14_vc15.exe/download))

**2.** The donwloaded file is a self-extracting archive. Double click on it 
and in the editable text field with title `Extract to:`, put the destination 
folder of your choice. `C:\` or `D:\` could be an excellent choice. We have 
decided to extract it into a specific folder on our platform that we dedicate 
to external libraries: `D:\Libs`.  
Once extraction will have completed, you'll get a new folder named `opencv` 
created and filled in the destination folder of your choice - for instance, 
resp. `C:\opencv`, `D:\opencv` or `D:\Libs\opencv`.



## 2. Configuring your projects for using OpenCV

### Linux

### Windows


<...in progress...>