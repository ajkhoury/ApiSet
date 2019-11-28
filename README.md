# ApiSet

API Set resolver written in C. This implementation supports API Set versions V2 to V6.

I wrote this to quickly resolve API Set libraries on different Windows OSes (Windows 7 - Windows 10 1909).

Usage:
`apiset.exe ext-some-api-set-library-l1-1-0.dll`

You can port this to work for kernel API sets quite easily by porting this to a small device driver.

Thanks to [lucasg](https://github.com/lucasg) for a great starting point for this little project.
