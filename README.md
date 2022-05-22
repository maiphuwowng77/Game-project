
# Game học phần Lập trình nâng cao : TREASURE HUNT
      21020783 - Lương Mai Phương
## I.	Hướng dẫn cài đặt:
-	Bước 1: Fork repository đó về tài khoản Github của mình.
-	Bước 2: Sao chép repository trên về máy local bằng lệnh: git clone https://github.com/[YOUR_USERNAME]/Game-project.git
-	Bước 3: Cài thư viện lập trình SDL2 và một số thư viện mở rộng của nó (SDL2_image, SDL2_ttf).
-	Bước 4: Chạy chương trình.
## II.	Mô tả chung về chương trình:
-	Game Treasure Hunt là một game vượt chướng ngại vật để tìm kiếm kho báu. Game có 3 level tương ứng với những độ khó khác nhau ( level càng cao thì càng nhiều vật cản và tốc độ của nhân vật cũng nhanh hơn). 

-	Nhiệm vụ trong game: Nhiệm vụ của bạn trong game là điều khiển nhân vật bằng các nút (←, →, ↑ , ↓) để tránh khỏi các chướng ngại vật (Bom và tường). Trên đường di chuyển sẽ xuất hiện các viên kim cương, bạn lấy được càng nhiều kim cương thì điểm số càng cao. Nhiệm vụ cuối của bạn là tìm đến chỗ của kho báu. Khi lấy được kho báu nhiệm vụ của bạn hoàn thành và bạn là người chiến thắng.
## III.	Các chức năng trong trò chơi:
-	Menu của game: Người chơi lựa chọn độ khó bằng các nút trên bàn phím theo hướng dẫn.
![Menu](https://drive.google.com/file/d/1kcDLxWzw8J5ctfofYteGBzHJvWN_6dwA/view?usp=sharing)
-	Đồ họa của game.
-	Nhận input từ bàn phím để di chuyển nhân vật
-	Chọn vị trí và đặt các quả bom trên đường đi. Khi nhân vật nằm trong vùng có bom với bán kính xác định, quả bom sẽ phát nổ, hình ảnh vụ nổ được hiện lên, người chơi thua cuộc.
-	Các viên kim cương được đặt rải rác khi nhân vật lấy được kim cương viên kim cương sẽ biến mất, một viên kim cương khác xuất hiện đồng thời điểm số của người chơi sẽ tăng.
-	Ở level 2 và 3, màn hình sẽ xuất hiện thêm 1 mê cung ( xây bằng gạch), người chơi phải di chuyển sao cho nhân vật không bị đâm vào tường, nếu bị đâm màn hình sẽ hiện vụ va chạm, trò chơi kết thúc và người chơi thua cuộc.
-	Ở góc cuối màn hình là kho báu mà người chơi cần chinh phục. Khi lấy được kho báu, số điểm của người chơi sẽ tăng và thắng cuộc.
![screen](https://scontent.xx.fbcdn.net/v/t1.15752-9/280415790_755693232232162_1012612004880580403_n.jpg?stp=dst-jpg_s261x260&_nc_cat=101&ccb=1-7&_nc_sid=aee45a&_nc_ohc=eDRblRFcBU8AX_jSBDZ&_nc_ad=z-m&_nc_cid=0&_nc_ht=scontent.xx&oh=03_AVK02uA_ukd6LsrSY85_hdqpmmddRSB4fM1Vc1jD7FbFkw&oe=62AD9D18)
-	Khi người chơi thắng cuộc có hiện số điểm mà người chơi đạt được.
-	Khi trò chơi kết thúc, người chơi ấn phím bất kì trên bàn phím để thoát chương trình.
## IV.	Các kỹ thuật lập trình được sử dụng trong chương trình:
-	Mảng ( các quả bom, tường và kim cương)
-	Con trỏ
-	Cấu trúc, lớp ( các lớp bom, kim cương, tường, người chơi và các hàm sử dụng để khởi tạo, hiện lên màn hình, di chuyển, xóa,…)
-	Thư viện lập trình SDL2 và các thư viện mở rộng của nó: Các hàm cơ bản trong thư viện.
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

