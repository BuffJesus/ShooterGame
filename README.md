\# ShooterGame - Unreal Engine 5.7 Port



A complete port of Epic Games' ShooterGame sample project from Unreal Engine 4.26 to Unreal Engine 5.7, featuring modern rendering technologies including \*\*Lumen\*\*, \*\*Nanite\*\*, \*\*Virtual Shadow Maps\*\*, and \*\*Temporal Super Resolution\*\*.



!\[Unreal Engine](https://img.shields.io/badge/Unreal%20Engine-5.7-blue)

!\[Lumen](https://img.shields.io/badge/Lumen-Enabled-orange)

!\[Nanite](https://img.shields.io/badge/Nanite-Ready-green)

!\[License](https://img.shields.io/badge/license-MIT-green)



\## Overview



This project is a working port of the classic ShooterGame template, originally designed for UE4, updated to compile and run on UE5.7. The port addresses numerous API changes, deprecated features, and enables modern UE5 rendering features.



\## Features



\- \*\*Lumen Global Illumination\*\* - Fully dynamic GI with software ray tracing

\- \*\*Lumen Reflections\*\* - Real-time dynamic reflections

\- \*\*Virtual Shadow Maps\*\* - High-quality shadows with infinite draw distance

\- \*\*Nanite Support\*\* - Ready for virtualized geometry (meshes need conversion)

\- \*\*Temporal Super Resolution (TSR)\*\* - Built-in upscaler for performance

\- \*\*Virtual Textures\*\* - Efficient texture streaming

\- \*\*Volumetric Fog\*\* - Atmospheric effects

\- \*\*DX12 by Default\*\* - Modern graphics API



\### Gameplay Features

\- Main Menu System with proper game state machine

\- Multiplayer Support (LAN, Steam, Online Subsystem)

\- AI Bots for Team Deathmatch and Free-for-All

\- Two Maps: Sanctuary and Highrise

\- Splitscreen local multiplayer



---



\## UE5.7 Rendering Features



\### Lumen Global Illumination



Lumen provides fully dynamic global illumination, replacing baked lightmaps with real-time bounce lighting.



```ini

r.DynamicGlobalIlluminationMethod=1

r.Lumen.DiffuseIndirect.Allow=True

r.Lumen.TraceMeshSDFs=1

```



\*\*Benefits:\*\*

\- No more lightmap baking required

\- Dynamic time of day support

\- Fully destructible environments maintain correct lighting



\### Lumen Reflections



Real-time reflections that respond to scene changes instantly.



```ini

r.ReflectionMethod=1

r.Lumen.Reflections.Allow=True

```



\### Virtual Shadow Maps (VSM)



Modern shadow system providing consistent quality at any distance.



```ini

r.Shadow.Virtual.Enable=1

r.Shadow.Virtual.MaxPhysicalPages=4096

```



\*\*Benefits:\*\*

\- No more shadow cascades to configure

\- Consistent shadow quality near and far

\- Better performance than traditional shadow maps



\### Nanite Virtualized Geometry



Nanite allows for extremely detailed meshes without LOD management.



```ini

r.Nanite.ProjectEnabled=True

r.Nanite.AllowMaskedMaterials=1

```



\*\*Note:\*\* To use Nanite, you must convert static meshes in the Editor:

1\. Select mesh in Content Browser

2\. Right-click → Nanite → Enable



\### Temporal Super Resolution (TSR)



UE5's built-in upscaler for better performance without sacrificing quality.



```ini

r.AntiAliasingMethod=4

r.TemporalAA.Upsampling=1

```



\### Hardware Ray Tracing (Optional)



For RTX/DXR capable hardware, uncomment these lines in `DefaultEngine.ini`:



```ini

r.RayTracing=True

r.Lumen.HardwareRayTracing=True

r.Lumen.HardwareRayTracing.LightingMode=2

```



---



\## Migration Changes (UE4 → UE5.7)



\### Core API Changes



\#### FTicker → FTSTicker



UE5 replaced `FTicker` with thread-safe `FTSTicker`:



```cpp

// Before (UE4)

TickDelegateHandle = FTicker::GetCoreTicker().AddTicker(TickDelegate);



// After (UE5)

TickDelegateHandle = FTSTicker::GetCoreTicker().AddTicker(TickDelegate);

```



\#### Platform Macro Safety



```cpp

// Before (UE4)

\#if PLATFORM\_PS4



// After (UE5)

\#if defined(PLATFORM\_PS4) \&\& PLATFORM\_PS4

```



\#### Map Name Comparison Fix



```cpp

// Before (UE4) - Broken in UE5

if (!MainMenuMap.Contains(Parm))



// After (UE5) - Proper comparison

const FString ShortMapName = FPackageName::GetShortName(Parm);

const FString ShortMainMenuMapName = FPackageName::GetShortName(MainMenuMap);

if (ShortMapName != ShortMainMenuMapName)

```



\### Deprecated API Handling



| API | Status | Workaround |

|-----|--------|------------|

| `EDemoPlayFailure` | Deprecated | `PRAGMA\_DISABLE\_DEPRECATION\_WARNINGS` |

| `SEARCH\_XBOX\_LIVE\_\*` | Removed | Local `#define` statements |

| `FOnlineEventParms` | Removed | Analytics code disabled |



\### Configuration Changes



| Setting | UE4 | UE5.7 |

|---------|-----|-------|

| `EditorStartupMap` | `/Game/Maps/Highrise` | `/Game/Maps/ShooterEntry` |

| `MinimumiOSVersion` | `IOS\_12` | Removed |

| `DefaultGraphicsRHI` | DX11 | DX12 |

| `r.DynamicGlobalIlluminationMethod` | N/A | `1` (Lumen) |

| `r.Shadow.Virtual.Enable` | N/A | `1` |



---



\## System Requirements



\### Minimum (Lumen Software)

\- \*\*GPU:\*\* GTX 1070 / RX 5700 or equivalent

\- \*\*VRAM:\*\* 6GB

\- \*\*DirectX:\*\* 12



\### Recommended (Lumen Hardware RT)

\- \*\*GPU:\*\* RTX 2070 / RX 6800 or equivalent  

\- \*\*VRAM:\*\* 8GB+

\- \*\*DirectX:\*\* 12 Ultimate



---



\## Building



\### Prerequisites



\- Unreal Engine 5.7

\- Visual Studio 2022 (Windows) or Xcode (Mac)

\- Git LFS for large file support



\### Steps



1\. Clone the repository:

&nbsp;  ```bash

&nbsp;  git lfs install

&nbsp;  git clone https://github.com/yourusername/shootergame-ue5.git

&nbsp;  ```



2\. Right-click `ShooterGame.uproject` and select "Generate Visual Studio project files"



3\. Open the generated solution and build



4\. Alternatively, open directly in Unreal Editor



---



\## Performance Tuning



\### Scalability Settings



The project supports UE5's scalability system. Adjust in-game or via config:



```ini

; High quality (default)

sg.ViewDistanceQuality=3

sg.AntiAliasingQuality=3

sg.ShadowQuality=3

sg.GlobalIlluminationQuality=3

sg.ReflectionQuality=3

sg.PostProcessQuality=3

sg.TextureQuality=3

sg.EffectsQuality=3

```



\### Lumen Quality vs Performance



For better performance on lower-end hardware:



```ini

; Lower Lumen quality

r.Lumen.DiffuseIndirect.Allow=False

r.ReflectionMethod=0

r.Shadow.Virtual.Enable=0

```



\### TSR Quality Presets



```ini

; Quality mode (native rendering)

r.TSR.History.ScreenPercentage=100



; Balanced (recommended)

r.TSR.History.ScreenPercentage=75



; Performance mode

r.TSR.History.ScreenPercentage=50

```



---



\## Command Line Options



| Option | Description |

|--------|-------------|

| `-vulkan` | Use Vulkan rendering (Linux/Windows) |

| `-dx11` | Use DirectX 11 (Windows) |

| `-dx12` | Use DirectX 12 (Windows, default) |

| `-benchmark` | Launch in benchmark mode |

| `-timeout=N` | Exit benchmark after N seconds |

| `-NoLumen` | Disable Lumen (use fallback GI) |

| `-NoNanite` | Disable Nanite |

| `-NoVSM` | Disable Virtual Shadow Maps |



---



\## Project Structure



```

ShooterGame/

├── Config/

│   ├── DefaultEngine.ini      # Rendering settings, Lumen, Nanite config

│   ├── DefaultGame.ini        # Game settings

│   └── DefaultInput.ini       # Input bindings

├── Content/

│   ├── Maps/                  # Sanctuary, Highrise, ShooterEntry

│   ├── Characters/            # Player and bot meshes

│   ├── Weapons/               # Rifle, Launcher

│   └── UI/                    # Menu assets

├── Source/

│   ├── ShooterGame/           # Main game module

│   └── ShooterGameLoadingScreen/

└── ShooterGame.uproject

```



---



\## Converting Assets for UE5 Features



\### Enabling Nanite on Meshes



1\. Select static mesh(es) in Content Browser

2\. Right-click → \*\*Nanite\*\* → \*\*Enable\*\*

3\. Save the mesh



\### Setting Up Lumen for Maps



Lumen works automatically, but for best results:



1\. Ensure meshes have proper \*\*Mesh Distance Fields\*\*

2\. Enable \*\*Generate Mesh Distance Field\*\* in mesh settings

3\. Use \*\*Lumen Scene\*\* lighting in Post Process Volume



\### Virtual Shadow Maps



VSM is enabled by default. For per-light control:

1\. Select light actor

2\. In Details panel, find \*\*Shadow\*\* settings

3\. Adjust \*\*Virtual Shadow Map\*\* options



---



\## Known Issues



| Issue | Description | Workaround |

|-------|-------------|------------|

| Missing Humanoid Skeleton | Character skeletons reference removed engine asset | Open and resave skeletons in Editor |

| Meshes not Nanite | Original meshes predate Nanite | Convert meshes: Right-click → Nanite → Enable |

| Baked lighting artifacts | Maps may have old UE4 lightmaps | Delete lightmap data, Lumen handles GI dynamically |

| Bot spawn warnings | Some spawn points have collision issues | Adjust PlayerStart positions if needed |



---



\## Credits



\- \*\*Original Project:\*\* Epic Games (ShooterGame Sample)

\- \*\*UE5 Port:\*\* BuffJesus

\- \*\*License:\*\* Content is licensed per Epic Games' sample content license. Code modifications are MIT licensed.



---



\## Version History



| Version | Engine | Changes |

|---------|--------|---------|

| 1.0 | UE 4.26 | Original Epic Games sample |

| 2.0 | UE 5.7 | Complete port with API updates |

| 2.1 | UE 5.7 | Added Lumen, Nanite, VSM, TSR support |



---



\## Contributing



Contributions are welcome! Please open an issue or submit a pull request for any improvements or bug fixes.



\### Areas for Contribution

\- Converting meshes to Nanite

\- Updating materials for Lumen

\- Performance optimization

\- Additional maps

