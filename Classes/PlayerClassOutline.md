# Player Class

## Attributes
(All public)

- **money**: Default 0
- **debt**: Default highly negative value
- **HP**: Health points
- **maxHP**: Default 25
- **hasShield**: Boolean
- **SP**: Shield health points

- **piloting**: Skill value to add when skill-checking
- **repair**: Skill value to add when skill-checking
- **bartering**: Skill value to add when skill-checking

## Methods

### Display Attributes Methods

- **getMoney()**: Return money for display
- **getDebt()**: Return debt for display
- **getHP()**: Return HP for display
- **getShieldHP()**: Return shield HP for display
- **getSkills()**: Return skills for display

### Change Attributes Methods

#### Money Methods

- **payMoney(amount, payee)**:
  - Decrease `money` by `amount`.
  - `payee` designates payDebt() vs market (money just disappears).

- **receiveMoney(amount)**:
  - Increase `money` by `amount`.
  - Can display money earned (missionBounty), and new total with `getMoney()`.

- **payDebt(amount)**:
  - Decrease `money` by `amount`, increase `debt` by `amount`.
  - Can display new debt with `getDebt()`.

#### Health Methods

- **takeDamage(amount, location)**:
  - Decrease health by `amount`.
  - `location` designates shield or HP by passing amount to `loseHP()`/`loseSP()`.

- **loseHP(amount)**:
  - Decrease `HP` by `amount`.
  - If `HP < 0`, trigger death.

- **lvlupHP()**:
  - Increase `maxHP` by 25.

#### Skill Methods

##FIXME
- add skill methods for interaction with missions
  

  
    
  

  
  
