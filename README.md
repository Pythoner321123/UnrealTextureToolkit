#A lightweight Unreal Engine C++ utility library for pixel-level GPU/CPU data interchange

UEColorDataToolkit is a small but powerful Unreal Engine C++ Blueprint Function Library that provides safe, easy-to-use helpers for converting GPU image data into CPU-friendly arrays — and back again.

This toolkit exposes three core operations:

Render Target → Color Array (GPU → CPU readback)

Color Array → Render Target (CPU → GPU write)

Color Array → Texture2D (CPU → GPU texture creation)

These functions streamline gameplay systems that require pixel manipulation, runtime drawing, image serialization, or saving/loading dynamic visual content.

🚀 Features
✔ GPU → CPU Image Extraction

Read pixels from a UTextureRenderTarget2D into a Blueprint-friendly TArray<FColor> so you can:

save drawings

serialize pixel data

process images with C++ or Blueprint logic

send data through online replication or save systems

✔ CPU → GPU Render Target Updating

Take any color array and push it directly onto a render target, making it visible in the world instantly.

✔ CPU → GPU Texture Generation

Convert raw pixel arrays into brand-new UTexture2D assets at runtime.

📦 Quick Overview of Included Functions
1. RenderTargetToColorArray(RenderTarget) → ColorArray

Reads all pixel data from the given RenderTarget into a CPU-side array.

Use When:

You want to save player drawings.

You need to serialize textures into a savegame or JSON.

You want to do CPU-side image processing.

2. ColorArrayToRenderTarget(Data, Target) → bool

Writes CPU pixel data into a Render Target.

Use When:

You're loading saved drawings.

You're dynamically generating images on the CPU.

You want to reconstruct visuals from arrays.

3. ColorArrayToTexture2D(Data) → Texture2D

Creates or updates a UTexture2D asset using raw pixel data.

Use When:

You need a permanent texture asset instead of a transient render target.

You want to use the image in UI, world meshes, materials, etc.

🧠 Typical Processing Order

If you're doing a full save/load cycle:

SAVE

1️⃣ Render Target → Color Array
2️⃣ Save Color Array in SaveGame / GameInstance / File

LOAD

3️⃣ Color Array → Render Target or Color Array → Texture2D

🔧 Installation & Setup
1. Add to Your C++ Project

Place the library .h and .cpp files into:

/Source/YourProject/Private
/Source/YourProject/Public

2. Add Module Dependencies

In your Build.cs:

PublicDependencyModuleNames.AddRange(new string[]
{
    "Core", "CoreUObject", "Engine", "RenderCore", "RHI"
});

3. Expose to Blueprint

Each function is UFUNCTION(BlueprintCallable) so the nodes appear automatically inside Blueprints under:

"Color Data Toolkit" Category

🧪 Example Use Cases
✏️ Player Drawing System

Capture strokes → update RenderTarget → save result → reload later.

🖼 Runtime Composite Graphics

Generate textures for:

crafting icons

in-world screens

map tiles

UI previews

📥 Import Pixel Data

Load images from disk → decode → fill a color array → create a texture in-game.

🎮 Sandbox / Factory Game Systems

(yes, perfect for your factorio-inspired systems)

store machine screen states

serialize production graphs as images

save inspection UIs as textures

📁 Repository Structure
UEColorDataToolkit/
│
├── Source/
│   ├── UEColorDataToolkit/
│   │   ├── ColorDataLibrary.h
│   │   ├── ColorDataLibrary.cpp
│
├── README.md  ← you are here
└── LICENSE

🤝 Contributing

Pull requests, improvements, and bug reports are welcome.
Please follow Unreal's formatting style (Allman brackets, PascalCase class names, etc.)

📝 License

MIT – free for commercial and non-commercial use.

🌟 Why This Library Exists

Unreal Engine provides several low-level ways to read/write pixel data, but they are verbose, unsafe, or not exposed to Blueprint.

This library wraps those operations into:

safe

blueprint-friendly

minimal

performant

utility functions that solve a common need in many games:
moving pixel data between CPU and GPU in both directions.

If you'd like, I can also generate:

✔ A logo
✔ Badges (build status, license, version, etc.)
✔ A sample project / demo code
✔ A .uproject plugin version
✔ API reference documentation

Just tell me!
