# GOES-16 Live Wallpaper

**This project is incomplete.** The goal of the project is to have an app that continuously sets your background to the
latest GeoColor full-disk picture from the GOES-16 weather satellite (the satellite provides a view of the Americas).
It should be light and as cross-platform as possible.

### Compatibility

I plan to support Windows, Mac OS X, and most Linux distributions.

### Isn't there already an app that does this?

Yes, and no. There is code on GitHub that can download images from the GOES-16 satellite, and there is also code that
continuously sets the desktop wallpaper to images from Himawari-8, a satellite with a view of the region around the
Indian and East Pacific oceans. There is no existing project that combines the two and updates the desktop to pictures
from GOES-16. The only exception I was able to find is this repo: https://github.com/cameronleger/goes16-background.
What makes this project different is that cameronleger's project is not cross-platform (doesn't even run on Windows),
uses Python, which introduces a dependency for the end-user, and needs to be externally run every fifteen minutes.
Also, my project uses GeoColor images, while cameronleger's uses natural color. It's close, but doesn't meet all the
requirements I've set for my own project.

### Why C++?

1. It's fast
1. Great library support
1. Compiler ubiquity
1. Personal preference for C++

### Repository structure

Development of the project will occur on the **develop** branch. This branch is **unstable**. In the future, stable
versions will be hosted on the **master** branch. When this project is ready for its first release, you can find it
there.
