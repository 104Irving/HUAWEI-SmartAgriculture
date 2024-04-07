import router from '@ohos.router'
import axios from '@ohos/axios'

const Params = router.getParams()
let userName = Params['userName']
let userPassword = Params['userPassword']

@Entry
@Component
struct LoadingPage{
  @State message: string = '少女祈祷中......'

  private timeID: number = 0 //计时器id

  aboutToAppear(){
    this.timeID = setInterval(()=>{

    }, 3000)

    axios({//传递到服务器请求用户登录和相关数据
      method:"get",
      url:'47.108.250.206:8080/GetUserData',
      params:{
        userName:userName
      }
    }).then(res=>{
      if(res.data){

        router.pushUrl({
          url:'pages/MainPage',
          //还需要式北来写全局变量更新：username,password
          params:{
            'userName': userName,
            'usrID': res.data.userID,
            'usrFarmList': res.data.List
          }
        })
      }else{//登录失败
        router.back({
          url:'pages/index',
          params:{}
        })
      }
    })
  }

  build(){
    Row(){
      Column(){
        Text(this.message)
          .fontSize(30)
          .fontWeight(FontWeight.Bold)
          .fontColor(Color.Black)

        LoadingProgress()
          .color(Color.Blue)
          .height(100)
          .width(100)
      }
      .width('100%')
    }
    .height('100%')
  }

  pageTransition(){
    PageTransitionEnter({ duration: 600 })
      .opacity(0)
    PageTransitionExit({ duration: 560 })
      .opacity(0)
  }
}