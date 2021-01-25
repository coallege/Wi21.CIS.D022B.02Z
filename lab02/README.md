# Itty Bitty Air Freight (IBA)

*Fun fact: this assignment hauls cargo*

An object oriented, Unit Load Delivery (ULD), setup and tracking program.
A Unit Load is one unit, either Container or Pallet to be loaded onto our Boeing 737.
Here’s your data to setup and manage:

Unit and type:

- Container or Pallet:
- AYF, AYK, AAA, AYY type Containers
- PAG, PMC, PLA type Pallets (a pallet is a flat platform for holding strapped down cargo).

Unit ID: Container or Pallet type: a five digit + airline code; our ID code is IB, e.g. AYF12345IB

Aircraft type: Ours is a 737; we are planning on adding more planes in the future of course.

Weight: The weight, in pounds, of the loaded container or pallet.

Destination: A three alpha character IATA string, e.g. MFR (Medford, OR), or PDX (Portland, OR)
