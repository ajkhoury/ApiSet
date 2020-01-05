# ApiSet

API Set resolver written in C. This implementation supports API Set versions V2 to V6.

The intended purpose of this tool is to resolve Windows API Set stub libraries for assisting in reverse engineering forwarded Windows API exports.

I wrote this to quickly resolve API Set libraries on different Windows OSes (Windows 7 - Windows 10 1909).

Usage:
`apiset.exe ext-some-api-set-library-l1-1-0.dll`

Thanks to [lucasg](https://github.com/lucasg) for a great starting point for this little project.
