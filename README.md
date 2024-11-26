# ZCU104 Sample Project with PSCDrv

## Components
- **fwk_prj**: FPGA Project for ZCU104  
- **ioc**: Barebones EPICS IOC for PSCDrv  
- **pscdrv**: Library for PSCDrv  
- **epics-base**: Library for base EPICS functionality  

---

## Cloning the Project
1. Clone the repository:  
   ```bash
   git clone git@gitlab.pbn.bnl.gov:kfahey/zcu104_pscdrv_test.git
   git submodule update --init --recursive
   ```

2. Configure `pscDrv`:
   - In `pscDrv/configure`, create the following files:
     - `CONFIG_SITE.local`:  
       ```plaintext
       USE_FFTW=YES
       ```
     - `RELEASE.local`:  
       ```plaintext
       EPICS_BASE=$(TOP)/../epics-base
       ```

3. Configure `ioc`:
   - In `ioc/configure`, create the file `RELEASE.local` with the following content:  
     ```plaintext
     PSCDRV=/path/to/project/pscdrv
     EPICS_BASE=/path/to/project/epics-base
     ```

---

## Building the Project

### IOC Side
1. Build `epics-base` and `pscdrv`:  
   ```bash
   make -C epics-base
   make -C pscdrv
   ```

2. Build the IOC:  
   ```bash
   cd ioc
   make
   ```

3. Make the run command executable:  
   ```bash
   chmod +x iocBoot/iocdemo/st.cmd
   ```

4. Run the IOC:  
   ```bash
   ./iocBoot/iocdemo/st.cmd
   ```

---

### FPGA Side
1. Build the hardware definition:
   ```bash
   make env
   make project cfg=hw
   make build cfg=hw
   ```

2. Build the software project:
   ```bash
   make project cfg=sw
   make build cfg=sw
   ```

> **Note**: Update the MAC address in the code to match the one displayed on the board. The EEPROM does not have the MAC address prewritten.

---

## Connection
- Modern Ethernet cards typically support interpreting straight-through cables as crossover, so no special cables are required for directly connecting devices during development.  
- Connect both devices to the same network and ensure the IP addresses match on both the software and IOC sides.
