import UserInfoBean from '../Common/Bean/UserInfoBean';
import { TabID, TabItemList } from '../model/TabItem';
import HomeComponent from '../view/HomeComponent';
import { MineComponent } from '../view/MineComponent';
import { WaterPlanComponent } from '../view/WaterPlanComponent';

@Entry
@Component
struct MainPage {
  public User: UserInfoBean = new UserInfoBean("s", "s", []);
  @State PageIndex: number = 0; //页面索引
  private tabController: TabsController = new TabsController();//tab转换控制器

  @Builder MyTabBuilder(idx: number){
    Column(){
      Image(idx == this.PageIndex ? TabItemList[idx].icon_selected : TabItemList[idx].icon)
        .width(32)
        .height(32)
      Text(TabItemList[idx].title)
        .fontSize(14)
        .fontWeight(FontWeight.Bold)
        .fontColor(this.PageIndex === idx ? '#006eee':'#888')
    }
  }

  build() {
    Tabs({barPosition:BarPosition.End}){
      TabContent(){
        HomeComponent({UserInfo:this.User})
      }
      .tabBar(this.MyTabBuilder(TabID.HOME))

      TabContent(){
        WaterPlanComponent()
      }
      .tabBar(this.MyTabBuilder(TabID.WATER_PLAN))

      TabContent(){
        MineComponent()
      }
      .tabBar(this.MyTabBuilder(TabID.MINE))
    }
    .barWidth('100%')
    .barMode(BarMode.Fixed)
    .width('100%')
    .height('100%')
    .scrollable(true)// 是否可滑动换页
    .onChange((index)=>{//绑定onChange函数切换页签
      this.PageIndex = index;
    })
  }
}




