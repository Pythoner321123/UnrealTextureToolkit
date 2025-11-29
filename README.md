# Unreal Image Conversion Library

A lightweight Unreal Engine C++ + Blueprint library for converting Render Targets, Textures, and raw Color Arrays.

📘 Overview

Unreal Image Conversion Library provides three essential low-level functions for handling GPU ↔ CPU image data inside Unreal Engine.

It exposes safe and Blueprint-friendly versions of common operations that developers normally struggle to implement on their own:

Read pixels from a Render Target into a CPU array

Write a CPU color array into a Render Target

Generate a Texture2D dynamically from a CPU color array

This is ideal for systems such as:

In-game painting

Screenshot capture & processing

Texture streaming

Data-driven UI

Procedural texture generation

Save/load image data

Pixel-based simulation systems

🚀 Features

✔ Render Target → Color Array (GPU → CPU)

✔ Color Array → Render Target (CPU → GPU)

✔ Color Array → Texture2D (CPU → GPU + asset creation)

✔ Fully Blueprint-exposed

✔ Designed for save/load systems

✔ Works with any pixel format supported by Unreal

✔ Lightweight, dependency-free C++

🔧 Functions
1. RenderTargetToColorArray

Direction: GPU → CPU
Reads pixel data from a UTextureRenderTarget2D and returns an array of FColor.

Use cases:

Saving a drawn canvas

Extracting visual data for gameplay logic

Serializing image states

2. ColorArrayToRenderTarget

Direction: CPU → GPU
Writes a given array of colors into an existing Render Target.

Use cases:

Loading saved drawings

Overwriting a render target with processed data

Displaying procedurally computed images

3. ColorArrayToTexture2D

Direction: CPU → GPU
Creates a new UTexture2D from a color array.

Use cases:

Creating UI icons dynamically

Converting raw image data into textures

Generating crafting/item icons at runtime

📦 Installation
1. Clone the Repository
git clone https://github.com/YourName/UnrealImageConversionLibrary.git

2. Add to Your Unreal Project

Place the plugin or source folder into your project's /Plugins or /Source directory.

Regenerate project files.

Recompile.

3. Enable From Editor

Edit → Plugins → Project → Image Conversion Library

🧩 Blueprint Usage Order

When doing Save & Load, use the functions in this order:

Saving Images

1️⃣ Render Target → Color Array
2️⃣ Store the Color Array (GI / SaveGame / Disk)

Loading Images

1️⃣ Retrieve stored Color Array
2️⃣ Color Array → Render Target or Color Array → Texture2D

📁 Folder Structure
/Source
    /ImageConversionLibrary
        ImageConversionLibrary.Build.cs
        Public/
            ColorArrayConversionBPLibrary.h
        Private/
            ColorArrayConversionBPLibrary.cpp

🧪 Example Blueprint Graph

✔ Read player’s drawing → Save color data
✔ Load color data → Restore drawing
✔ Display restored drawing on any mesh or widget

📚 Documentation Goals

This library is meant to solve common problems such as:

Why can’t I save a Render Target?

Why can’t I serialize a Material Instance Dynamic?

How do I convert GPU textures into UObject assets?

How do I get pixel-accurate data into Blueprints?

With these functions, you finally can.

🛠 Future Improvements

Texture compression helpers

PNG/JPEG loading (optional)

Async CPU/GPU copy operations

Mip-generation helpers

Material Instance → Serialized Metadata support

🧑‍💻 Contribution

Pull requests are welcome!
Please open an issue for feature requests or bug reports.

📄 License

MIT License — free for commercial and non-commercial use.

If you want, I can also generate:
✅ GitHub repo description
✅ Repository tags
✅ A professional project logo (via image generation)
✅ Sample C++ usage
✅ A wiki page structure

Just say the word.
