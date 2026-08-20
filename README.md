# 🏹 **Platform Forge**

##🎮 **Giới thiệu chung**

- **Thành viên nhóm:**
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

# Platform Forge

####📖 **Mục lục**

## Mục lục

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
   * [4.2. Câu lệnh chạy chương trình](#42-câu-lệnh-chạy-chương-trình)

5. [Hướng dẫn sử dụng](#5-hướng-dẫn-sử-dụng)
   * [5.1. Điều khiển nhân vật](#51-điều-khiển-nhân-vật)
   * [5.2. Chế độ tạo và chỉnh sửa Map](#52-chế-độ-tạo-và-chỉnh-sửa-map)

6. [Các chức năng đã hoàn thành](#6-các-chức-năng-đã-hoàn-thành)

7. [Báo cáo và Video Demo](#7-báo-cáo-và-video-demo)
   * [7.1. Báo cáo PDF](#71-báo-cáo-pdf)
   * [7.2. Video Demo](#72-video-demo)

---

## 1. Giới thiệu

### 1.1. Mô tả bài toán

**Platform Forge** là trò chơi platform 2D được xây dựng bằng C++ theo hướng lập trình hướng đối tượng. Người chơi điều khiển nhân vật di chuyển qua các khu vực của bản đồ, vượt qua địa hình và chướng ngại vật, tương tác với các đối tượng trong game, tránh hoặc xử lý các loại enemy và thu thập vật phẩm trong quá trình chơi.

Bên cạnh gameplay platform truyền thống, hệ thống còn tích hợp **chế độ chỉnh sửa bản đồ**, cho phép người dùng thay đổi các thành phần của map như platform và decor ngay trong chương trình. Qua đó, project không chỉ tập trung vào việc xây dựng gameplay mà còn hướng đến khả năng tạo và tùy chỉnh nội dung bản đồ.

### 1.2. Mục tiêu

Mục tiêu của project là xây dựng một game platform 2D hoàn chỉnh ở mức cơ bản, đồng thời áp dụng các kiến thức về C++, lập trình hướng đối tượng và xử lý đồ họa thời gian thực.

Các mục tiêu chính gồm:

* Xây dựng hệ thống điều khiển và chuyển động của nhân vật.
* Xử lý trọng lực, nhảy, leo thang và va chạm với môi trường.
* Xây dựng bản đồ từ các tile và platform.
* Xây dựng nhiều loại đối tượng trong game như enemy, item, item box, spike, switch, coin và diamond.
* Xây dựng hệ thống camera theo dõi nhân vật.
* Sử dụng animation và tài nguyên hình ảnh để thể hiện trạng thái của các đối tượng.
* Xây dựng hệ thống giao diện phục vụ quá trình chơi game.
* Cho phép người dùng chỉnh sửa, trang trí và lưu bản đồ thông qua chế độ tạo map.
* Tổ chức source code thành các module độc lập để thuận tiện cho việc phát triển, bảo trì và mở rộng.

### 1.3. Phạm vi hệ thống

Trong phạm vi của project, hệ thống tập trung vào các thành phần chính sau:

* **Gameplay:** điều khiển nhân vật, di chuyển, nhảy, leo thang và tương tác với môi trường.
* **Map:** quản lý platform, tile, decor và các đối tượng được bố trí trên bản đồ.
* **Enemy:** quản lý các loại kẻ địch với hành vi và cách tương tác khác nhau.
* **Item:** cung cấp các vật phẩm có khả năng ảnh hưởng đến trạng thái hoặc kỹ năng của người chơi.
* **Điểm số:** người chơi có thể thu thập coin và diamond để tăng điểm.
* **Collision:** phát hiện và xử lý va chạm giữa player với platform, item, enemy và các đối tượng khác.
* **Map Editor:** hỗ trợ chỉnh sửa platform, decor và lưu lại bản đồ.
* **Camera và Animation:** hỗ trợ hiển thị bản đồ theo vị trí người chơi và thể hiện chuyển động của các đối tượng.
* **Giao diện:** bao gồm các thành phần hỗ trợ người chơi như menu, tạm dừng, game over, cài đặt và hướng dẫn chơi.
* **Âm thanh và tài nguyên:** quản lý texture, animation và sound được sử dụng trong game.

Project tập trung vào việc xây dựng một **game platform 2D chạy trên máy tính**, với gameplay và công cụ chỉnh sửa map được tích hợp trong cùng một chương trình.


---

## 2. Công nghệ và môi trường

### 2.1. Công nghệ sử dụng

Project được phát triển chủ yếu bằng **C++** và sử dụng thư viện **SDL3** để xây dựng game 2D.

Các công nghệ và thư viện chính:

| Công nghệ         | Mục đích sử dụng                                               |
| ----------------- | -------------------------------------------------------------- |
| **C++**           | Ngôn ngữ lập trình chính của project                           |
| **SDL3**          | Tạo cửa sổ, xử lý sự kiện, bàn phím, chuột và render đồ họa 2D |
| **SDL3_image**    | Hỗ trợ tải và xử lý các tài nguyên hình ảnh sử dụng trong game |
| **SDL3_ttf**      | Hỗ trợ hiển thị văn bản và font chữ                            |
| **Visual Studio** | IDE sử dụng để phát triển, biên dịch và chạy project           |
| **Git / GitHub**  | Quản lý source code và lưu trữ repository                      |

Source code được tổ chức theo hướng **lập trình hướng đối tượng**, trong đó các thành phần như Player, Enemy, Map, Item, Tile, Animation, Camera và UI được tách thành các class/module riêng.

---

### 2.2. Môi trường chạy

Project hiện được phát triển và kiểm thử trên môi trường:

* **Hệ điều hành:** Windows
* **IDE:** Microsoft Visual Studio
* **Ngôn ngữ:** C++
* **Thư viện đồ họa:** SDL3
* **Thư viện hình ảnh:** SDL3_image
* **Thư viện font chữ:** SDL3_ttf

Các thư viện SDL được đặt trực tiếp trong project:

```text
SDL3/
SDL3_image/
SDL3_ttf/
src/
```

Do đó project không phụ thuộc vào việc cài SDL3 toàn cục trên hệ thống nếu cấu hình đường dẫn thư viện trong Visual Studio đã được thiết lập đúng.

---

### 2.3. Yêu cầu cài đặt

Để biên dịch và chạy project, máy tính cần có:

1. **Windows 10/11** hoặc môi trường Windows có hỗ trợ Visual Studio.

2. **Microsoft Visual Studio** có cài workload:

   ```text
   Desktop development with C++
   ```

3. Trình biên dịch C++ đi kèm Visual Studio.

4. Các thư viện SDL cần thiết:

   ```text
   SDL3
   SDL3_image
   SDL3_ttf
   ```

   Các thư viện này hiện đã được tổ chức trong repository của project.

---

## 3. Cấu trúc dự án

Project được tổ chức theo hướng module hóa, trong đó mỗi nhóm chức năng của game được tách thành các thư mục và class riêng. Cách tổ chức này giúp source code dễ quản lý, bảo trì và mở rộng.

### 3.1. Cấu trúc thư mục

Cấu trúc chính của project:

```text
Platform Forge  /
│
│
├── src/                            # Mã nguồn chính
│   │
│   ├── engine/                     # Các thành phần lõi của game
│   │   ├── UI/                     # Hệ thống giao diện
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
│   │   ├── Animation.cpp
│   │   ├── Animation.h
│   │   ├── camera.cpp
│   │   ├── camera.h
│   │   ├── resourceManager.cpp
│   │   ├── resourceManager.h
│   │   ├── soundManager.cpp
│   │   └── soundManager.h
│   │
│   ├── GameObject/                 # Các đối tượng trong game
│   │   │
│   │   ├── Enemy/                  # Kẻ địch
│   │   │   ├── enemy.cpp
│   │   │   ├── enemy.h
│   │   │   ├── flyer.cpp
│   │   │   ├── flyer.h
│   │   │   ├── walker.cpp
│   │   │   └── walker.h
│   │   │
│   │   ├── engine/                 # Render đối tượng
│   │   │   ├── render.cpp
│   │   │   └── render.h
│   │   │
│   │   ├── Player/                 # Người chơi
│   │   │   ├── player.cpp
│   │   │   └── player.h
│   │   │
│   │   ├── Special/                # Các vật phẩm đặc biệt
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
│   │   ├── Tile/                   # Các đối tượng bản đồ
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
│   ├── Map/                        # Quản lý bản đồ
│   │   ├── Map.cpp
│   │   └── Map.h
│   │
│   ├── Scene/                      # Quản lý các màn hình / scene
│   │   ├── scene.cpp
│   │   ├── scene.h
│   │   ├── sceneEditor.cpp
│   │   ├── sceneEditor.h
│   │   ├── sceneMain.cpp
│   │   ├── sceneMain.h
│   │   ├── sceneMenu.cpp
│   │   └── sceneMenu.h
│   │
│   └── main.cpp                    # Điểm bắt đầu chương trình
│
└── SDL3.dll                        # Thư viện SDL3 khi chạy
```

Trong đó:

* `SDL3/`, `SDL3_image/`, `SDL3_ttf/`: chứa các thư viện SDL được sử dụng trong project.
* `src/`: chứa toàn bộ source code chính của game.
* `engine/`: chứa các thành phần dùng chung của game engine.
* `GameObject/`: chứa các đối tượng xuất hiện trong game.
* `Map/`: quản lý dữ liệu và các đối tượng của bản đồ.
* `Scene/`: quản lý các scene và luồng hoạt động của game.
* `main.cpp`: điểm bắt đầu của chương trình.

---

### 3.2. Các module chính

#### `GameObject`

Là module cơ sở cho các đối tượng xuất hiện trong game.

Class `gameObject` đóng vai trò lớp nền, cung cấp các thuộc tính chung như:

* Vị trí `x`, `y`.
* Kích thước của đối tượng.
* Texture.
* Vùng render.
* Các hàm cập nhật và hiển thị cơ bản.

Các đối tượng cụ thể được xây dựng dựa trên cấu trúc này.

---

#### `Player`

Quản lý nhân vật do người chơi điều khiển.

Module này chịu trách nhiệm cho:

* Di chuyển trái và phải.
* Nhảy.
* Trọng lực.
* Leo thang.
* Animation theo trạng thái.
* Xử lý trạng thái đứng trên mặt đất.
* Thu thập và sử dụng các loại item.
* Các hiệu ứng đặc biệt như:

  * Double Jump.
  * No Gravity.
  * High Jump.
  * Speed Boost.
  * Star.
  * Heart.

---

#### `Enemy`

Quản lý các đối tượng kẻ địch trong game.

Enemy được chia thành nhiều loại khác nhau, ví dụ:

```text
Enemy
├── enemy
├── walker
└── flyer
```

Việc tách các loại enemy thành class riêng giúp mỗi loại có thể được xây dựng với cách di chuyển, hành vi và cơ chế tương tác khác nhau.

---

#### `Tile`

Quản lý các thành phần cấu thành môi trường của bản đồ.

Các đối tượng chính gồm:

* `platform`: nền và bề mặt người chơi có thể đứng.
* `ladder`: cho phép nhân vật leo lên hoặc xuống.
* `spike`: chướng ngại vật gây nguy hiểm.
* `switch`: công tắc tương tác với các thành phần trong map.
* `decor`: các đối tượng trang trí bản đồ.

Các tile được sử dụng để xây dựng địa hình và gameplay cho từng khu vực.

---

#### `Special`

Chứa các đối tượng đặc biệt và vật phẩm trong game.

Bao gồm:

```text
Special
├── Item
├── ItemBox
├── Coin
└── Diamond
```

Trong đó:

* `Item`: các vật phẩm hỗ trợ hoặc thay đổi trạng thái người chơi.
* `ItemBox`: hộp chứa vật phẩm hoặc kích hoạt chức năng đặc biệt.
* `Coin`: vật phẩm thu thập để tăng điểm.
* `Diamond`: vật phẩm có giá trị dùng để tăng điểm cho người chơi.

---

#### `Map`

Module `Map` chịu trách nhiệm quản lý nội dung của bản đồ.

Các đối tượng được quản lý trong Map bao gồm:

* Player.
* Enemy.
* Platform.
* Decor.
* Switch.
* Item Box.
* Item.
* Camera.

Module này cũng đảm nhiệm việc cập nhật vị trí render của các đối tượng dựa trên camera và hỗ trợ các chức năng phục vụ việc chỉnh sửa bản đồ.

---

#### `Scene`

Quản lý các trạng thái và màn hình khác nhau của game.

`sceneMain` là scene chính trong quá trình chơi và chịu trách nhiệm:

* Nhận input từ bàn phím và chuột.
* Cập nhật các đối tượng.
* Render map và GameObject.
* Xử lý va chạm.
* Xử lý tương tác với item.
* Xử lý tương tác với enemy.
* Điều khiển camera theo player.
* Quản lý Pause, Game Over và các trạng thái liên quan trong quá trình chơi.

Việc chia game thành các scene giúp chuyển đổi giữa các màn hình và trạng thái của chương trình dễ dàng hơn.

---

#### `engine`

Chứa các thành phần dùng chung hỗ trợ toàn bộ game.

Các module chính gồm:

| Module            | Chức năng                                                            |
| ----------------- | -------------------------------------------------------------------- |
| `Animation`       | Quản lý animation và frame của các đối tượng                         |
| `camera`          | Quản lý góc nhìn và vị trí camera                                    |
| `resourceManager` | Quản lý và cung cấp các tài nguyên như texture                       |
| `soundManager`    | Quản lý âm thanh trong game                                          |
| `UI`              | Chứa các thành phần giao diện như Pause Menu, Settings, Game Over... |

Việc tập trung các chức năng dùng chung vào `engine` giúp tránh lặp code giữa các đối tượng và scene khác nhau.

---

#### `main.cpp`

`main.cpp` là điểm bắt đầu của chương trình.

File này chịu trách nhiệm khởi tạo các thành phần cần thiết của ứng dụng và bắt đầu vòng lặp chính của game. Từ đây chương trình quản lý việc xử lý sự kiện, cập nhật trạng thái và render các scene lên cửa sổ game.


---

## 4. Cài đặt và chạy chương trình

### 4.1. Biên dịch chương trình

**Cách 1: Visual Studio**

* Build: `Build > Build Solution` hoặc `Ctrl + Shift + B`
* File `.exe` nằm trong: `x64/Debug` hoặc `x64/Release`

**Cách 2: Command line**

```bash
msbuild <project-name>.sln /p:Configuration=Debug /p:Platform=x64
msbuild <project-name>.sln /p:Configuration=Release /p:Platform=x64
```

---

### 4.2. Chạy chương trình

**Trong Visual Studio:**

* `Ctrl + F5` hoặc bấm dấu mũi tên ->(Run)

**Chạy file .exe:**

```bash
cd x64\Debug
<game-name>.exe
```

---

## 5. Hướng dẫn sử dụng

### 5.1. Điều khiển nhân vật

| Phím            | Chức năng                 |
| --------------- | ------------------------- |
| `A / ←`         | Di chuyển trái            |
| `D / →`         | Di chuyển phải            |
| `W / SPACE / ↑` | Nhảy / leo lên            |
| `S / ↓`         | Leo xuống                 |
| `ESC`           | Tạm dừng / đóng giao diện |

### 5.2. Chế độ tạo Map

| Phím      | Chức năng                |
| --------- | ------------------------ |
| `F1 / F2` | Bật / tắt chế độ tạo map |
| `TAB`     | Mở Decor                 |
| `← / →`   | Chọn loại platform       |
| `L`       | Lưu map                  |

Người chơi cần tránh spike và enemy, đồng thời thu thập **coin** và **diamond** để tăng điểm.


---

## 6. Các chức năng đã hoàn thành

* **Điều khiển nhân vật:** hỗ trợ di chuyển trái/phải, nhảy, leo thang và thay đổi animation theo trạng thái của nhân vật.

* **Hệ thống vật lý và va chạm:** xử lý trọng lực, va chạm giữa Player với platform, item box, ladder, spike, switch và các đối tượng khác trong bản đồ.

* **Enemy:** xây dựng hệ thống kẻ địch với nhiều loại như Walker và Flyer. Mỗi loại enemy có cách di chuyển và cơ chế tương tác với người chơi khác nhau.

* **Item và Item Box:** người chơi có thể tương tác với các hộp vật phẩm để nhận các item đặc biệt như Star, Double Jump, No Gravity, High Jump, Heart và Speed Boost.

* **Coin, Diamond và điểm số:** hỗ trợ thu thập vàng và kim cương trong quá trình chơi để tăng điểm của người chơi.

* **Map và Tile:** xây dựng bản đồ từ nhiều loại đối tượng như platform, ladder, spike, switch và decor, đồng thời quản lý vị trí các đối tượng theo camera.

* **Map Editor:** hỗ trợ chế độ tạo/chỉnh sửa map, lựa chọn platform, thêm decor và lưu lại bản đồ.

* **Camera và Animation:** camera tự động theo dõi vị trí Player; hệ thống animation hiển thị các trạng thái Idle, Run, Jump và các chuyển động của đối tượng.

* **Giao diện game:** đã xây dựng Pause Menu, Game Over Menu, Settings Menu và bảng hướng dẫn chơi.

* **Quản lý tài nguyên và âm thanh:** sử dụng Resource Manager để quản lý texture và Sound Manager để quản lý các hiệu ứng âm thanh của game.

* **Quản lý Scene:** tổ chức các trạng thái của game theo Scene, hỗ trợ chuyển đổi giữa màn hình chơi, menu và chế độ chỉnh sửa map.

---

## 7. Báo cáo và Video Demo

### 7.1. Báo cáo PDF

Báo cáo mô tả quá trình phân tích, thiết kế, xây dựng và hoàn thiện project.

**Link báo cáo:** https://drive.google.com/file/d/1w40VXIQwkELdxQswXbbQMPltI29r5L2E/view?usp=sharing

### 7.2. Video Demo

Video trình bày các chức năng chính của game, gameplay và chế độ tạo/chỉnh sửa map.

**Link video demo:** https://drive.google.com/file/d/1DYFZDQrw3zWb_MIQ-Oif4VdVUv9F35T2/view?usp=sharing

