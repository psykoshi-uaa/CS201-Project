# Upgrade Class Outline

## Properties

- **Name**: The name of the upgrade (e.g., “Reinforced Hull”, “Cargo Hold S, M, L, XL,” “MortCorp Certification”, etc.).
- **Cost**: The cost of the upgrade.
- **Attribute**: The attribute that the upgrade affects (e.g., “HP”, “Shield”, “Cargo”, “Speed”, “Fuel”).
- **Effect**: The effect on the attribute (e.g., +25 HP, +10 Speed).

## Constructor

- Initializes the upgrade with a name, cost, attribute, and effect.

## Getters

_Not sure if we’ll need these ‘getters’ but it may be useful for tracking particular upgrades._

- `getName()`: Returns the name of the upgrade.
- `getCost()`: Returns the cost of the upgrade.
- `getAttribute()`: Returns the attribute that the upgrade affects.
- `getEffect()`: Returns the effect on the attribute.

## Setters

- `setName(std::string newName)`: Sets the name of the upgrade.
- `setCost(int newCost)`: Sets the cost of the upgrade.
- `setAttribute(std::string newAttribute)`: Sets the attribute that the upgrade affects.
- `setEffect(int newEffect)`: Sets the effect on the attribute for the upgrade (+5, for instance).
