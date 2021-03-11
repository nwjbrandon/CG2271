## CG2271 Project

### Setup
- Create new project
 1) Create new project
 2) Expand NXP then KLxx Series, then KL2x and then select MKL25Z128xxx4
 3) Select CMSIS->Core and Device->Startup in Manage Run Time window 

- Add new directories
 1) Right click on "Target Souce 1"
 2) Click on "Add Group"
 3) Rename folder by selecting manage group item on right click

- Add new files
 1) Select on folder and add new file to group
 2) Ensure file is in the src or include folder
 
- Import files
 1) Add files to folder by selecting manage group item on right click
 2) Select files to add to group
 
### Run
- Click on the compile button
- Click on the debug button
- Click on the run button

### Errors
- No device found
 1) Click on "Options for target" -> Select the tab "Debug" -> Use "CMSIS-DAP-debugger"
 2) Click on "Options for target" -> Select the tab "Target" -> Check "Use MicroLIB"