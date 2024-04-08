import UserInfoBean from '../Common/Bean/UserInfoBean';
import { MainTabID, MainTabItemList } from '../model/TabItem';
import HomeComponent from '../view/HomeComponent';
import { MineComponent } from '../view/MineComponent';
import router from '@ohos.router';
import FarmBean from '../Common/Bean/Farmbean';
import axios from '@ohos/axios';

//从loading界面获取到的用户数据
const Params = router.getParams()
const userName = Params['userName']
const userID = Params['usrID']
const usrFarmList = Params['usrFarmList']

//测试用数据
// const userName = "测试用户"
// const userID = 0
// const usrFarmList = [0,1,2,3,4,5,6,7]


@Entry
@Component
struct MainPage {
  private timeID:number = 0 //计时器id
  public User: UserInfoBean = new UserInfoBean(userName, userID, usrFarmList);
  @State PageIndex: number = 0; //页面索引
  // @State FarmList:FarmBean[] = []//农田的列表
  @State FarmList:FarmBean[] = [
    // new FarmBean(0, '测试农田',0,0,0,0,0, false),
    // new FarmBean(0, '测试农田',0,0,0,0,0, false),
    // new FarmBean(2, '测试农田',0,0,0,0,0, false),
    // new FarmBean(3, '测试农田',0,0,0,0,0, false),
    // new FarmBean(4, '测试农田',0,0,0,0,0, false),
  ]//农田的列表

  @State show: boolean = true


  private tabController: TabsController = new TabsController();//tab转换控制器

  // null  @State ResData:any =

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

  //更新农田数据
  loadFarmData(){
    for (let index = 0;index < this.User.UserFarmList.length; index++){

      axios({//传递到服务器请求用户管理农田的相关数据
        method:"get",
        url:'47.108.250.206:8080/FarmData',
        params:{
          UserID: this.User.UserID,                 //用户ID
          FarmID: this.User.UserFarmList[index],    //将该用户的管理的农田的列表上传
        }
      }).then(res=>{

        setTimeout(() => {
          console.log(JSON.stringify(res))
          this.FarmList[index] = new FarmBean(
            this.User.UserFarmList[index], //农田ID number
            res.data["farmName"], //农田名 string
            res.data["wendu"], //温度 number
            res.data["kongqishidu"], //空气湿度 number
            res.data["co2nongdu"], //二氧化碳浓度 number
            res.data["gzqiangdu"], //光照强度 number
            res.data["turangshidu"], //土壤湿度 number
            false
          )
        }, 50)
      })

      this.FarmList[index] = new FarmBean(
        this.User.UserFarmList[index],
        '测试',
        Math.random(),
        Math.random(),
        Math.random(),
        Math.random(),
        Math.random(),
        false
      )
      console.log(`${this.FarmList[index].If_show}`)
    }
  }

  aboutToAppear(){
    //获取农田初始数据
    this.loadFarmData();

    //每一秒更新一次农田数据
    this.timeID = setInterval(()=>{
      this.loadFarmData()
    }, 10000)
  }

  onPageShow(){
    console.log('PageShow')
  }

  //主构造体
  build() {
    Tabs({barPosition:BarPosition.End}){
      //主页
      TabContent(){
        if (this.show || !this.show){
          HomeComponent({
            UserInfo: this.User,
            MyFarmList:this.FarmList
          })
        }
      }
      .tabBar(this.MyTabBuilder(MainTabID.HOME))

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

  //页面转换
  pageTransition(){
    PageTransitionEnter({ duration: 600 })
      .opacity(0)
    PageTransitionExit({ duration: 600 })
      .opacity(0)
  }
}




