import UserInfoBean from '../Common/Bean/UserInfoBean';
import { MainTabID, MainTabItemList } from '../model/TabItem';
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
      Image(idx == this.PageIndex ? MainTabItemList[idx].icon_selected : MainTabItemList[idx].icon)
        .width(32)
        .height(32)
      Text(MainTabItemList[idx].title)
        .fontSize(14)
        .fontWeight(FontWeight.Bold)
        .fontColor(this.PageIndex === idx ? '#006eee':'#888')
    }
  }

  build() {
    Tabs({barPosition:BarPosition.End}){
      //主页
      TabContent(){HomeComponent({UserInfo:this.User})}
      .tabBar(this.MyTabBuilder(MainTabID.HOME))
      //灌溉计划
      // TabContent(){WaterPlanComponent()}
      // .tabBar(this.MyTabBuilder(MainTabID.WATER_PLAN))
      //用户页面
      TabContent(){MineComponent()}
      .tabBar(this.MyTabBuilder(MainTabID.MINE))
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

  pageTransition(){
    PageTransitionEnter({ duration: 600 })
      .opacity(0)
    PageTransitionExit({ duration: 600 })
      .opacity(0)
  }
}




