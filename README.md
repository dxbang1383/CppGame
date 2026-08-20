# 🏹 **Platform Forge**

## 🎮 **Giới thiệu chung**

- 👥 **Thành viên nhóm:**
  - **Đỗ Xuân Bằng**  
    - **Mã sinh viên:** 24021383
    - **Nhiệm vụ:** Xây map, tìm ảnh, hoàn thiện cửa sổ game, hoàn thiện camera, hướng di chuyển toàn map, thực hiện việc chuyển đổi từ platform sang map và tạo map mới.
  - **Trần Mạnh Chiến**  
    - **Mã sinh viên:** 24021395
    - **Nhiệm vụ:** Thực hiện xử lí animation cho nhân vật, tìm ảnh, xử lí các icon như các item, vật cản,... hoàn thiện powerup các hiệu ứng trong game.
  - **Lê Trung Hiếu**  
    - **Mã sinh viên:** 24021475
    - **Nhiệm vụ:** Thực hiện việc xử lí animation cho enemy, hoàn thiện các tác vụ như menu, hướng dẫn, xử lí âm thanh cho các đối tượng có trong game.

- **Project:** Platform Forge  


## 🏹 **Platform Forge**


## 🗺️Mục lục

1. [Giới thiệu](#1-giới-thiệu)
   * [1.1. Mô tả bài toán](#11-mô-tả-bài-toán)
   * [1.2. Mục tiêu](#12-mục-tiêu)
   * [1.3. Phạm vi hệ thống](#13-phạm-vi-hệ-thống)

2. [Công nghệ và môi trường](#2-công-nghệ-và-môi-trường)
   * [2.1. Công nghệ sử dụng](#21-công-nghệ-sử-dụng)
   * [2.2. Môi trường chạy](#22-môi-trường-chạy)
   * [2.3. Yêu cầu cài đặt](#23-yêu-cầu-cài-đặt)

3. [Cấu trúc dự án](#3-cấu-trúc-dự-án)
   * [3.1. Cấu trúc thư mục](#31-cấu-trúc-thư-mục)
   * [3.2. Các module chính](#32-các-module-chính)

4. [Cài đặt và chạy chương trình](#4-cài-đặt-và-chạy-chương-trình)
   * [4.1. Biên dịch chương trình](#41-biên-dịch-chương-trình)
   * [4.2. Chạy chương trình](#42-chạy-chương-trình)

5. [Hướng dẫn sử dụng](#5-hướng-dẫn-sử-dụng)
   * [5.1. Điều khiển nhân vật](#51-điều-khiển-nhân-vật)
   * [5.2. Chế độ tạo và chỉnh sửa Map](#52-chế-độ-tạo-và-chỉnh-sửa-map)

6. [Các chức năng đã hoàn thành](#6-các-chức-năng-đã-hoàn-thành)

7. [Báo cáo và Video Demo](#7-báo-cáo-và-video-demo)
   * [7.1. Báo cáo PDF](#71-báo-cáo-pdf)
   * [7.2. Video Demo](#72-video-demo)

---

## 🎮 1. Giới thiệu

### 🕹️ 1.1. Mô tả bài toán

**Platform Forge** là game platform 2D được xây dựng bằng C++, nơi người chơi điều khiển nhân vật **khám phá bản đồ 🗺️, vượt chướng ngại vật ⚠️, đối đầu với enemy 👾 và thu thập vật phẩm 💎**.

Điểm nổi bật của game là **Map Editor 🛠️**, cho phép người chơi tự do chỉnh sửa platform, decor và tạo ra những bản đồ theo ý muốn.

### 🎯 1.2. Mục tiêu

Project hướng đến việc xây dựng một game platform 2D hoàn chỉnh ở mức cơ bản, đồng thời vận dụng kiến thức về **C++, OOP và xử lý đồ họa thời gian thực**.

Các mục tiêu chính:

* 🎮 Điều khiển nhân vật, nhảy, leo thang và xử lý va chạm.
* 🧱 Xây dựng bản đồ với platform, tile, decor và các chướng ngại vật.
* 👾 Xây dựng enemy, item, coin và diamond.
* 🎞️ Tạo hệ thống camera và animation sinh động.
* 🖥️ Xây dựng menu, pause, game over, settings và hướng dẫn.
* 🛠️ Hỗ trợ **tạo, chỉnh sửa và lưu map** ngay trong game.
* 🧩 Tổ chức chương trình theo các module rõ ràng, dễ phát triển và mở rộng.

### 🌍 1.3. Phạm vi hệ thống

Game tập trung vào các chức năng chính:

* 🎮 **Gameplay:** di chuyển, nhảy, leo thang và tương tác với môi trường.
* 🗺️ **Map & Map Editor:** xây dựng, chỉnh sửa và lưu bản đồ.
* 👾 **Enemy:** nhiều loại kẻ địch với cách di chuyển khác nhau.
* 💎 **Item & Score:** thu thập item, coin và diamond để tăng điểm.
* 💥 **Collision:** xử lý va chạm giữa nhân vật và các đối tượng.
* 📷 **Camera & Animation:** theo dõi nhân vật và tạo chuyển động trực quan.
* 🔊 **UI & Sound:** menu, pause, game over, settings, hướng dẫn và âm thanh.

✨ Nhìn chung, **Platform Forge** kết hợp gameplay platform truyền thống với khả năng **tự tạo và tùy chỉnh bản đồ**, mang lại trải nghiệm vừa **chơi 🎮** vừa **sáng tạo 🛠️**.

---

## 💻 2. Công nghệ và môi trường

### 🛠️ 2.1. Công nghệ sử dụng

**Platform Forge** được phát triển bằng **C++**, sử dụng **SDL3** để xây dựng game 2D và **Visual Studio** làm môi trường phát triển.

| Công nghệ            | Mục đích                             |
| -------------------- | ------------------------------------ |
| 🟦 **C++**           | Ngôn ngữ lập trình chính             |
| 🎮 **SDL3**          | Cửa sổ, sự kiện và đồ họa 2D         |
| 🖼️ **SDL3_image**   | Tải và xử lý hình ảnh                |
| 🔤 **SDL3_ttf**      | Hiển thị font và văn bản             |
| 💻 **Visual Studio** | Viết, biên dịch và chạy chương trình |
| 🌐 **Git / GitHub**  | Quản lý source code                  |

Source code được tổ chức theo hướng **lập trình hướng đối tượng (OOP)**, với các module chính như **Player, Enemy, Map, Item, Tile, Animation, Camera và UI**.

---

### 🖥️ 2.2. Môi trường chạy

* 🪟 **Hệ điều hành:** Windows 10/11
* 💻 **IDE:** Microsoft Visual Studio
* 🟦 **Ngôn ngữ:** C++
* 🎮 **Đồ họa:** SDL3
* 🖼️ **Hình ảnh:** SDL3_image
* 🔤 **Font:** SDL3_ttf

Các thư viện được đặt trực tiếp trong project:

```text
SDL3/
SDL3_image/
SDL3_ttf/
src/
```

---

### ⚙️ 2.3. Yêu cầu cài đặt

Để build và chạy game, cần:

1. 🪟 **Windows 10/11**
2. 💻 **Microsoft Visual Studio** với workload:

   ```text
   Desktop development with C++
   ```
3. 🔧 Trình biên dịch C++ đi kèm Visual Studio.
4. 🎮 Các thư viện:

   ```text
   SDL3
   SDL3_image
   SDL3_ttf
   ```

Các thư viện SDL đã được tích hợp trong repository của project.


---

## 🏗️ 3. Cấu trúc dự án

Project được tổ chức theo hướng **module hóa**, trong đó mỗi nhóm chức năng được tách thành các thư mục và class riêng, giúp source code dễ **quản lý, bảo trì và mở rộng**.

### 📁 3.1. Cấu trúc thư mục

Cấu trúc chính của project:

```text
Platform Forge/
│
├── src/                            # 💻 Mã nguồn chính
│   │
│   ├── engine/                     # ⚙️ Các thành phần lõi của game
│   │   ├── UI/                     # 🖥️ Hệ thống giao diện
│   │   │   ├── Button.cpp
│   │   │   ├── Button.h
│   │   │   ├── GameOverMenu.cpp
│   │   │   ├── GameOverMenu.h
│   │   │   ├── Menu.cpp
│   │   │   ├── Menu.h
│   │   │   ├── Palette.cpp
│   │   │   ├── Palette.h
│   │   │   ├── PauseMenu.cpp
│   │   │   ├── PauseMenu.h
│   │   │   ├── SettingsMenu.cpp
│   │   │   ├── SettingsMenu.h
│   │   │   ├── Text.cpp
│   │   │   └── Text.h
│   │   │
│   │   ├── Animation.cpp            # 🎞️ Animation
│   │   ├── Animation.h
│   │   ├── camera.cpp               # 📷 Camera
│   │   ├── camera.h
│   │   ├── resourceManager.cpp      # 📦 Quản lý tài nguyên
│   │   ├── resourceManager.h
│   │   ├── soundManager.cpp         # 🔊 Quản lý âm thanh
│   │   └── soundManager.h
│   │
│   ├── GameObject/                  # 🎮 Các đối tượng trong game
│   │   │
│   │   ├── Enemy/                   # 👾 Kẻ địch
│   │   │   ├── enemy.cpp
│   │   │   ├── enemy.h
│   │   │   ├── flyer.cpp
│   │   │   ├── flyer.h
│   │   │   ├── walker.cpp
│   │   │   └── walker.h
│   │   │
│   │   ├── engine/                  # 🎨 Render đối tượng
│   │   │   ├── render.cpp
│   │   │   └── render.h
│   │   │
│   │   ├── Player/                  # 🧑 Người chơi
│   │   │   ├── player.cpp
│   │   │   └── player.h
│   │   │
│   │   ├── Special/                 # 💎 Vật phẩm đặc biệt
│   │   │   ├── coin.cpp
│   │   │   ├── coin.h
│   │   │   ├── diamond.cpp
│   │   │   ├── diamond.h
│   │   │   ├── item.cpp
│   │   │   ├── item.h
│   │   │   ├── itemBox.cpp
│   │   │   ├── itemBox.h
│   │   │   └── specialObject.h
│   │   │
│   │   ├── Tile/                    # 🧱 Các đối tượng bản đồ
│   │   │   ├── decor.cpp
│   │   │   ├── decor.h
│   │   │   ├── ladder.h
│   │   │   ├── platform.h
│   │   │   ├── spike.h
│   │   │   ├── switch.h
│   │   │   ├── teleport.h
│   │   │   ├── tile.cpp
│   │   │   └── tile.h
│   │   │
│   │   ├── gameObject.cpp
│   │   └── gameObject.h
│   │
│   ├── Map/                        # 🗺️ Quản lý bản đồ
│   │   ├── Map.cpp
│   │   └── Map.h
│   │
│   ├── Scene/                      # 🎬 Quản lý các Scene
│   │   ├── scene.cpp
│   │   ├── scene.h
│   │   ├── sceneEditor.cpp
│   │   ├── sceneEditor.h
│   │   ├── sceneMain.cpp
│   │   ├── sceneMain.h
│   │   ├── sceneMenu.cpp
│   │   └── sceneMenu.h
│   │
│   └── main.cpp                    # 🚀 Điểm bắt đầu chương trình
│
└── SDL3.dll                        # 🔧 Thư viện SDL3 khi chạy
```

### 🔎 Các thành phần chính

* 📦 **`src/`**: chứa toàn bộ source code của game.
* ⚙️ **`engine/`**: chứa các thành phần dùng chung như Animation, Camera, Resource Manager, Sound Manager và UI.
* 🎮 **`GameObject/`**: quản lý các đối tượng xuất hiện trong game.
* 🗺️ **`Map/`**: quản lý dữ liệu và các đối tượng của bản đồ.
* 🎬 **`Scene/`**: quản lý các màn hình và trạng thái hoạt động của game.
* 🚀 **`main.cpp`**: điểm bắt đầu của chương trình.
* 🎮 **`SDL3/`, `SDL3_image/`, `SDL3_ttf/`**: các thư viện SDL được sử dụng trong project.

---

### 🧩 3.2. Các module chính

#### 🎮 `GameObject`

Module cơ sở cho các đối tượng trong game, quản lý **vị trí, kích thước, texture, vùng render** và các thao tác cập nhật/hiển thị.

#### 🧑 `Player`

Quản lý nhân vật người chơi: **di chuyển, nhảy, trọng lực, leo thang, animation, va chạm** và sử dụng item.

Các hiệu ứng nổi bật gồm **Double Jump, No Gravity, High Jump, Speed Boost, Star và Heart**.

#### 👾 `Enemy`

Quản lý kẻ địch với các loại chính:

```text
Enemy
├── enemy
├── walker
└── flyer
```

Mỗi loại có cách di chuyển và hành vi riêng.

#### 🧱 `Tile`

Quản lý các thành phần môi trường của map:

* `platform` — nền và bề mặt di chuyển.
* `ladder` — leo lên/xuống.
* `spike` — chướng ngại vật nguy hiểm.
* `switch` — công tắc tương tác.
* `decor` — trang trí bản đồ.

#### 💎 `Special`

Quản lý các vật phẩm và đối tượng đặc biệt:

```text
Special
├── Item
├── ItemBox
├── Coin
└── Diamond
```

Dùng để hỗ trợ người chơi và tăng điểm trong quá trình chơi.

#### 🗺️ `Map`

Quản lý **bản đồ và các đối tượng** như Player, Enemy, Platform, Decor, Switch, Item và Camera, đồng thời hỗ trợ các chức năng chỉnh sửa map.

#### 🎬 `Scene`

Quản lý các màn hình và trạng thái game. `sceneMain` đảm nhiệm **input, cập nhật, render, va chạm, tương tác, camera, Pause và Game Over**.

#### ⚙️ `engine`

Chứa các thành phần dùng chung:

| Module               | Chức năng                           |
| -------------------- | ----------------------------------- |
| 🎞️ `Animation`      | Quản lý animation và frame          |
| 📷 `camera`          | Quản lý góc nhìn                    |
| 📦 `resourceManager` | Quản lý texture và tài nguyên       |
| 🔊 `soundManager`    | Quản lý âm thanh                    |
| 🖥️ `UI`             | Menu, Pause, Settings, Game Over... |

#### 🚀 `main.cpp`

Điểm bắt đầu của chương trình, thực hiện **khởi tạo game và chạy vòng lặp chính** để xử lý sự kiện, cập nhật và hiển thị game.



---

## 🚀 4. Cài đặt và chạy chương trình

### 🔨 4.1. Biên dịch chương trình

**💻 Cách 1: Visual Studio 2022**

1. Mở **Visual Studio 2022**.
2. Chọn **File → Open → Folder** và chọn thư mục dự án.
3. CMake tự động nhận diện `CMakeLists.txt`.
4. Chọn preset **x64-release**.
5. Chọn **Build All**.

**💻 Cách 2: VS Code**

1. Mở folder dự án trong **VS Code**.
2. Cài extension **C/C++** và **CMake Tools**.
3. Chọn **CMake: Select a Kit → MSVC**.
4. Chọn **CMake: Select Variant → Release**.
5. Chọn **CMake: Build**.

---

### ▶️ 4.2. Chạy chương trình

**💻 Cách 1: Visual Studio 2022**

1. Mở **Visual Studio 2022**.
2. Chọn **File → Open → Folder** và chọn folder dự án.
3. CMake sẽ tự động tìm `CMakeLists.txt` và generate.
4. Chọn preset **x64-release**.
5. Chọn **Build All** hoặc chạy chương trình.

**💻 Cách 2: VS Code**

1. Mở folder dự án trong **VS Code**.
2. Cài extension **C/C++** và **CMake Tools**.
3. Chọn **CMake: Select a Kit → MSVC**.
4. Chọn **CMake: Select Variant → Release**.
5. Chọn **CMake: Build**.
6. Chạy file:

```bash
./out/build/x64-release/CppGame.exe
```

---


## 🎮 5. Hướng dẫn sử dụng

### 🕹️ 5.1. Điều khiển nhân vật

| Phím               | Chức năng                 |
| ------------------ | ------------------------- |
| ⬅️ `A / ←`         | Di chuyển trái            |
| ➡️ `D / →`         | Di chuyển phải            |
| ⬆️ `W / SPACE / ↑` | Nhảy / leo lên            |
| ⬇️ `S / ↓`         | Leo xuống                 |
| ⏸️ `ESC`           | Tạm dừng / đóng giao diện |

### 🛠️ 5.2. Chế độ tạo Map

| Phím          | Chức năng                |
| ------------- | ------------------------ |
| 🗺️ `F1 / F2` | Bật / tắt chế độ tạo map |
| 🎨 `TAB`      | Mở Decor                 |
| ◀️▶️ `← / →`  | Chọn loại platform       |
| 💾 `L`        | Lưu map                  |

### 🎯 Mục tiêu khi chơi

Người chơi cần **né spike ⚠️ và enemy 👾**, đồng thời thu thập **coin 🪙 và diamond 💎** để tăng điểm và hoàn thành màn chơi.


---

## ✅ 6. Các chức năng đã hoàn thành

* 🎮 **Điều khiển nhân vật:** di chuyển trái/phải, nhảy, leo thang và animation theo trạng thái.
* ⚡ **Vật lý & va chạm:** xử lý trọng lực và va chạm với platform, item box, ladder, spike, switch và các đối tượng khác.
* 👾 **Enemy:** xây dựng Walker và Flyer với cách di chuyển và tương tác khác nhau.
* 🎁 **Item & Item Box:** tương tác với hộp vật phẩm và nhận các item như Star, Double Jump, No Gravity, High Jump, Heart và Speed Boost.
* 🪙 **Coin, Diamond & điểm số:** thu thập coin và diamond để tăng điểm.
* 🧱 **Map & Tile:** xây dựng map với platform, ladder, spike, switch và decor, kết hợp cùng hệ thống camera.
* 🛠️ **Map Editor:** tạo, chỉnh sửa platform, thêm decor và lưu map.
* 🎞️ **Camera & Animation:** camera theo dõi Player và animation cho các trạng thái Idle, Run, Jump cùng các chuyển động khác.
* 🖥️ **Giao diện:** Pause Menu, Game Over Menu, Settings Menu và hướng dẫn chơi.
* 📦 **Tài nguyên & âm thanh:** Resource Manager quản lý texture và Sound Manager quản lý hiệu ứng âm thanh.
* 🎬 **Scene:** tổ chức các trạng thái game và chuyển đổi giữa gameplay, menu và chế độ chỉnh sửa map.

---

## 📚 7. Báo cáo và Video Demo

### 📄 7.1. Báo cáo PDF

Báo cáo trình bày quá trình **phân tích, thiết kế, xây dựng và hoàn thiện** project.

**🔗 Link báo cáo:**
https://drive.google.com/file/d/1w40VXIQwkELdxQswXbbQMPltI29r5L2E/view?usp=sharing

### 🎥 7.2. Video Demo

Video giới thiệu **gameplay, các chức năng chính và chế độ tạo/chỉnh sửa map**.

**🔗 Link video demo:**
https://drive.google.com/file/d/1DYFZDQrw3zWb_MIQ-Oif4VdVUv9F35T2/view?usp=sharing

