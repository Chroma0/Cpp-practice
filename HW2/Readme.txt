class Item :儲存X軸Y軸位置及方向

Item::temp(int x,int y,int dir) :使用時將X軸數值,Y軸數值,方向數值傳入 用以設置Item中的各項值

int direction_x(int a) :使用時將方向數值傳入,回傳該方向的X軸變化量

int direction_y(int a) :使用時將方向數值傳入,回傳該方向的Y軸變化量

void Path(const int m,const int p) :列印並記錄每個STEP的位置以及判斷是否能到達終點

int main():主程式