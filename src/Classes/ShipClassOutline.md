# Starship Class Outline

## Attributes

### 1. Basic Attributes:
- `string name` - The name of the starship.
- `int HP` - Current health points.
- `int maxHP` - Maximum health points.
- `bool hasShield` - Indicates if the shield is enabled by an upgrade.
- `int shield` - Current shield points.
- `int maxShield` - Maximum shield points.
- `int cargoCapacity` - Maximum cargo capacity. Upgrading unlocks new tiers of hauler missions.
- `int speed` - Speed of the starship. Provides a +% to cargo missions and -% damage in combat missions.

### 2. Weapons:
- `std::vector<Weapon> weapons` - List of weapons equipped on the starship. These can be accessed fairly easily, looped through, added, and removed as necessary with a vector.

### 3. Upgrades:
- `std::vector<Upgrade> upgrades` - List of applied upgrades. These can be accessed fairly easily, looped through, added, and removed as necessary with a vector.

## Methods

### 1. Constructor:
- Initialize all attributes with default or specified values.

### 2. Getters:
- Methods to get the current values of attributes (e.g., `getHP()`, `getMaxHP()`, `getShield()`, `getMaxShield()`, `getCargoCapacity()`, `getSpeed()`, `getWeapons()`, `getUpgrades()`, etc.)

### 3. Setters:
- Methods to set or update the values of attributes (e.g., `setHP(int newHP)`, `setShield(int newShield)`, etc.).

### 4. Upgrade Methods:
- `void ApplyUpgrade(Upgrade)` - Apply an upgrade to the starship, adding it to the list of applied upgrades.
- `void ShowUpgrades() const` - Display the list of applied upgrades.

### 5. Combat Methods:
- `void TakeDamage(int amount)` - Apply damage to the starship, affecting shields first, then HP.
- `void Repair(int amount)` - Repair the starship’s HP.
- `void Refuel(int amount)` - Refuel the starship.
- `void AddCargo(int amount)` - Add cargo to the starship.
- `void RemoveCargo(int amount)` - Remove cargo from the starship.
- `void FireWeapons()` - Use the starship’s weapons.
