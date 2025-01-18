# Simulation of the RPC Detector Array for MuonID  

## Description  
This project simulates a Resistive Plate Chamber (RPC) detector array, consisting of 320 RPCs arranged around a cylindrical steel absorber.  

The simulation is designed to:  
- Generate muons with energies ranging from 1 GeV to 5 GeV.  
- Muons came from the origin of the mother volume in random directions, within a pseudorapidity range up to \(\eta = 1.5\).  
- Record the energy deposited in the detector's gas gaps.  
- Calculate the geometric efficiency of the Muon Identification Detector (MID).  

## Key Components  
- **DetectorConstruction.cc**: Defines the entire detector geometry.  
- **PrimaryGenerationAction**: Configures the muon gun and defines particle generation properties.  
- **Event**: Allows configuration for measuring either geometric efficiency or total deposited energy.  

## Prerequisites  
- **Geant4** installed and configured.  
- A C++ environment (e.g., GCC, Visual Studio).  
- Optional: A compatible visualization interface with Geant4 to observe the simulation.
- 
## Visualization Examples
Three screenshots are included to demostrate the expected visualization.

## Additional Version
A version for measuring time of flight and deposited charge is also available. For more information, feel free to contact victorhuggh@gmail.com.

## Contributions 
If you wish to contribute to this project, feel free to open an issue or submit a pull request.
