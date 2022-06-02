
# Game học phần Lập trình nâng cao : TREASURE HUNT
- Họ và tên: Lương Mai Phương
- MSV: 21020783
- Lớp môn học: INT2215_1, nhóm 9
## Mục lục:
- [I.	Hướng dẫn cài đặt](#i-hướng-dẫn-cài-đặt)
- [II. Mô tả chung về chương trình](#ii-mô-tả-chung-về-chương-trình)
- [III. Các chức năng trong trò chơi](#iii-các-chức-năng-trong-trò-chơi)
- [IV. Các kỹ thuật lập trình được sử dụng trong chương trình](#iv-các-kỹ-thuật-lập-trình-được-sử-dụng-trong-chương-trình)
- [V.	Kết luận](#v-kết-luận)

<a name = "i-hướng-dẫn-cài-đặt"/>

## I.	Hướng dẫn cài đặt:
### Cài đặt MinGW-W64:
- Download MinGW-W64 GCC-7.3.0-SEH tại link https://sourceforge.net/projects/mingw-w64/files/Toolchains%20targetting%20Win64/Personal%20Builds/mingw-builds/7.3.0/threads-win32/seh/x86_64-7.3.0-release-win32-seh-rt_v5-rev0.7z/download
- Giải nén file x86_64-7.3.0-release-win32-seh-rt_v5-rev0.7z
- Copy thư mục `mingw64` vào **<ROOTDIR>** (Ví dụ `D:\software`)
- Cài đặt đường dẫn PATH đến **<ROOTDIR>\mingw64\bin**
```
💡 Kiểm tra bằng cách gọi g++ và mingw32-make trong terminal

```
### Tải chương trình về máy tính cá nhân và chạy chương trình:
-	Bước 1: Fork repository này về tài khoản Github của mình.
- Bước 2: Sử dụng ứng dụng vscode (nếu chưa có tải về tại link https://code.visualstudio.com/download) 
-	Bước 3: Sao chép repository trên về máy local bằng lệnh: git clone https://github.com/[YOUR_USERNAME]/Game-project.git tại mục terminal của vscode
-	Bước 4: Chạy chương trình bằng các lệnh sau ở mục terminal:
```
 cd Game-project
 mingw32-make
 .\main.exe
 ```
<a name = "ii-mô-tả-chung-về-chương-trình"/>

## II. Mô tả chung về chương trình:
-	Game Treasure Hunt là một game vượt chướng ngại vật để tìm kiếm kho báu. Game có 3 level tương ứng với những độ khó khác nhau ( level càng cao thì càng nhiều vật cản và tốc độ của nhân vật cũng nhanh hơn). 

-	Nhiệm vụ trong game: Nhiệm vụ của bạn trong game là điều khiển nhân vật bằng các nút (←, →, ↑ , ↓) để tránh khỏi các chướng ngại vật (Bom và tường). Trên đường di chuyển sẽ xuất hiện các viên kim cương, bạn lấy được càng nhiều kim cương thì điểm số càng cao. Nhiệm vụ cuối của bạn là tìm đến chỗ của kho báu. Khi lấy được kho báu nhiệm vụ của bạn hoàn thành và bạn là người chiến thắng.

<a name = "iii-các-chức-năng-trong-trò-chơi"/>

## III.	Các chức năng trong trò chơi:
### Video minh họa sản phẩm: https://www.youtube.com/watch?v=t5bNhSYSl40
-	Menu của game: Người chơi lựa chọn độ khó bằng các nút trên bàn phím theo hướng dẫn.

 ![Menu](https://i.imgur.com/yELhLJj.jpg)

-	Đồ họa của game.
-	Nhận input từ bàn phím để di chuyển nhân vật
-	Chọn vị trí và đặt các quả bom trên đường đi. Khi nhân vật nằm trong vùng có bom với bán kính xác định, quả bom sẽ phát nổ, hình ảnh vụ nổ được hiện lên, người chơi thua cuộc.

![explode](https://i.imgur.com/K7eg355.jpg)

-	Các viên kim cương được đặt rải rác khi nhân vật lấy được kim cương viên kim cương sẽ biến mất, một viên kim cương khác xuất hiện đồng thời điểm số của người chơi sẽ tăng.
-	Ở level 2 và 3, màn hình sẽ xuất hiện thêm 1 mê cung ( xây bằng gạch), người chơi phải di chuyển sao cho nhân vật không bị đâm vào tường, nếu bị đâm màn hình sẽ hiện vụ va chạm, trò chơi kết thúc và người chơi thua cuộc.

![collision](https://i.imgur.com/MaZ54dx.jpg)

-	Ở góc cuối màn hình là kho báu mà người chơi cần chinh phục. Khi lấy được kho báu, số điểm của người chơi sẽ tăng và thắng cuộc.

![screen](https://i.imgur.com/xj3BKPX.jpg)

-	Khi người chơi thắng cuộc có hiện số điểm mà người chơi đạt được.

![score](https://i.imgur.com/F1XrKKk.jpg)

-	Khi trò chơi kết thúc, người chơi ấn phím bất kì trên bàn phím để thoát chương trình.

<a name = "iv-các-kỹ-thuật-lập-trình-được-sử-dụng-trong-chương-trình"/>

## IV.	Các kỹ thuật lập trình được sử dụng trong chương trình:
-	Mảng ( các quả bom, tường và kim cương)
-	Cấu trúc, lớp ( các lớp bom, kim cương, tường, người chơi và các hàm sử dụng để khởi tạo, hiện lên màn hình, di chuyển, xóa,…)
-	Thư viện lập trình SDL2 và các thư viện mở rộng của nó: Các hàm cơ bản trong thư viện.

<a name = "v-kết-luận"/>

## V.	Kết luận:
### Nguồn tham khảo:
-	Cách sử dụng thư viện SDL2 trên trang https://lazyfoo.net/tutorials/SDL/
-	Hình ảnh nhân vật, quả bom, kim cương, tường, rương kho báu tham khảo trên mạng và tự vẽ lại trên trang https://www.pixilart.com
-	Hình ảnh game over, win, vụ nổ, vụ va chạm được lấy trên mạng.
-	Hình ảnh menu,score tự thiết kế.
###	Điều tâm đắc:
 Đã có thể tự sáng tạo ra một dự án game nhỏ bằng cách vận dụng những kiến thức có được trong bộ môn lập trình nâng cao, có thể sử dụng các hàm cơ bản trong thư viện lập trình SDL2 và một số thư viện mở rộng của nó.
### Hướng phát triển : 
-	Thêm âm thanh để trò chơi thêm sinh động
-	Thêm mục hướng dẫn trong menu
-	Thêm phần lưu giữ high score từ các lần chơi trước
-	Tạo ra nhiều level với độ khó cao và hình ảnh đa dạng hơn nữa
- Tạo ra chức năng chơi lại

