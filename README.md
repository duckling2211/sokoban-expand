# Sokoban mở rộng

## Luật chơi
1. Điều khiển nhân vật `@` theo hướng dẫn trong chương trình.
2. Đẩy các hộp `*` vào các vị trí đích `.`.
3. Đẩy tất cả hộp vào các vị trí đích sẽ qua màn, và tự động chuyển màn tiếp theo.

## Cơ chế bổ sung
1. Đẩy `*` vào `F` sẽ thua màn, vào `B` sẽ phá cả hai.
2. Đẩy `*` vào `-`, `<`, `>` sẽ làm mất hộp, `@` rớt vào sẽ thua màn.
3. Đẩy `R` vào `-` sẽ tạo lối, vào `<` hay `>` sẽ trôi theo hướng đó đến cuối và tạo đường.
