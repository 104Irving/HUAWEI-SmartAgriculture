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

@Entry
@Component
struct MainPage {
  private timeID:number = 0 //计时器id

  public User: UserInfoBean = new UserInfoBean(userName, userID, usrFarmList);
  @State PageIndex: number = 0; //页面索引
  @State FarmList:FarmBean[] = []//农田的列表
  private tabController: TabsController = new TabsController();//tab转换控制器

  @State ResData:any = null

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
        //res.data.list.
        if(res.data){//获得数据
          this.ResData = res.data.FarmList[index] // ResData还是一个数组
          this.FarmList[index] = new FarmBean(
            this.User.UserFarmList[index], //农田ID number
            res.data.FarmName, //农田名 string
            res.data.Temperature, //温度 number
            res.data.humidity, //空气湿度 number
            res.data.co2, //二氧化碳浓度 number
            res.data.lumination, //光照强度 number
            res.data.soilHumidity, //土壤湿度 number
          )
        }else{//数据获取失败
          // 数据获取失败的处理 todo
        }
      })
    }

    // axios({//传递到服务器请求用户管理农田的相关数据
    //   method:"get",
    //   url:'47.108.250.206:8080/GetFarmSensorData',
    //   params:{
    //     userName: this.User.Username,
    //     UserFarmList: this.User.UserFarmList,//将该用户的管理的农田的列表上传
    //   }
    // }).then(res=>{
    //   if(res.data){//获得数据
    //     for (let index = 0; index < this.User.UserFarmList.length; index++) {
    //       this.ResData = res.data.FarmList[index] // ResData还是一个数组
    //       this.FarmList[index] = new FarmBean(
    //         this.ResData[0], //农田ID number
    //         this.ResData[1], //农田名 string
    //         this.ResData[2], //温度 number
    //         this.ResData[3], //空气湿度 number
    //         this.ResData[4], //二氧化碳浓度 number
    //         this.ResData[5], //光照强度 number
    //         this.ResData[6], //土壤湿度 number
    //       )
    //     }
    //   }else{//数据获取失败
    //     // 数据获取失败的处理
    //   }
    // })
  }

  aboutToAppear(){
    //获取农田初始数据
    this.loadFarmData();

    //每一秒更新一次农田数据
    this.timeID = setInterval(()=>{
      this.loadFarmData()
    }, 1000)
  }

  //主构造体
  build() {
    Tabs({barPosition:BarPosition.End}){
      //主页
      TabContent(){HomeComponent({MyFarmList:this.FarmList})}
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

  //页面转换
  pageTransition(){
    PageTransitionEnter({ duration: 600 })
      .opacity(0)
    PageTransitionExit({ duration: 600 })
      .opacity(0)
  }
}




