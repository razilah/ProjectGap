# Gap – GASP + GAS Combat Framework (UE5.7)

Project Gap is a Unreal Engine 5 prototype that integrates **Motion Matching (GASP)** with the **Gameplay Ability System (GAS)** to create a TPS Hack & Slash Shooter.

This project focuses on gameplay systems architecture, input-driven abilities, and attribute-driven UI rather than polished game content.

---

## 🔧 Engine & Dependencies

- Unreal Engine 5.7  
- Gameplay Ability System (GAS)  
- Gameplay Animation Sample Project (GASP) - as base project 
- Enhanced Input System  
- C++ Core Gameplay Module  

---

## 🎮 Input System Overview

Input is handled using **UE5 Enhanced Input** and mapped to **Gameplay Abilities via Gameplay Tags**.

### 🔹 Input Mapping Context
| Action | Key | Gameplay Tag | Description |
|--------|------|--------------|-------------|
| Move | WASD | — | Locomotion via Motion Matching |
| Look | Mouse | — | Camera control |
| Jump | Space | — | Jump via Motion Matching |
| Heavy Attack | LMB | `Ability.Combat.Attack` | Line trace attack with finisher combo with AOE |
| Heal | Q | `Ability.Main.Heal` | Support skill with AOE using TargetActor |
| Dash | E | `Ability.Movement.Dash` | Dash ability |

Abilities are triggered through **ASC Input Binding → Gameplay Tags → Ability Activation**.

---

## ⚙️ Gameplay Ability System Architecture

### 🔹 Core Classes

| Class | Description |
|--------|-------------|
| `GapCharacter` | Base GAS-enabled character |
| `PlayerCharacter` | GAS-enabled player character |
| `EnemyCharacter` | GAS-enabled enemy character |
| `GapAbilitySystemComponent` | Custom ASC wrapper |
| `GapAttributeSet` | Health attributes |
| `GameplayAbility` | Base class for all abilities |
| `GapPlayerController` | Input → Ability binding layer |
| `DA_AbilityList` | GAS granted ability list |

---

### 🔹 Attributes

| Attribute | Purpose |
|------------|----------|
| Health | Damage and death handling |

Attributes replicate and notify UI via **Gameplay Attribute Change Delegates**.

---

## ⚔️ Combat System

### ✅ Combo System
- Heavy attack support **multi-hit combos**
- Combo window handled via **Anim Notify State**
- Combo resets after inactivity (~2s)

### ✅ Hit Detection
- Line Trace for single-target melee hits  
- Sphere Trace for finisher AOE attacks
- Sphere Trace for heal ability with Target Actor

### ✅ Motion Matching Integration
- Locomotion driven by GASP Motion Matching
- Combat abilities override locomotion states via **GAS Ability Tags**

---

## 🖥️ UI System

UI is built with **UMG + Attribute Binding**.

### HUD Elements
- Health Bar  
- Mana Bar  
- Stamina Bar  
- Ability Cooldown Indicators (WIP)  

