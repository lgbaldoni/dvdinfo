######################################################
#  DVDx InfoTool project for Mac.X, Linux and Win32
#
#  Version: 0.9.2
#  License: GNU GPL
#  Author & copyright: Starbuck<starbuck@labdv.com>
#  Date: 06-Jan-2008
######################################################

This pre-release uses libdvdread to get DVD informations
from IFO files (VOB files aren't parsed and can even be
absent from the VIDEO_TS folder). The libdvdread gives 
DVD and titles informations but not VTS (Video Title Set) 
data, the next version of DVDx InfoTool will compute VTS 
and PGC data to provide the VTS details with longest PGC
which is more useful for DVD player or DVD ripper users.

To do:

- fix crash on Matrix NTSC (all platforms)
- add a progress bar for title info processing
- fix can't open Ifo which occurs for many titles
- fix recent files display in Linux version

Licensing
---------
Read the file COPYING. DVDx InfoTool is licensed under the 
GNU General Public License.
