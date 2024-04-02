import router from '@ohos.router'
import axios from '@ohos/axios'

const Params = router.getParams()

let userName = Params['userName']
let userPassword = Params['userPassword']

@Entry
@Component
struct LoadingPage{
  @State message: string = '少女祈祷中......'

  aboutToAppear(){
    axios({//传递到服务器请求用户登录和相关数据
      method:"get",
      url:'47.108.250.206:8080/login',
      params:{
        userName:userName,
        userPassword:userPassword
      }
    }).then(res=>{
      if(res.data){
        router.pushUrl({
          url:'pages/MainPage',
          //还需要式北来写全局变量更新：username,password
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

        // Button('登陆')
        //   .width('95%') .margin({top:10})
          // .onClick(() =>{
          //
          //   // router.pushUrl({
          //   //   url: 'pages/MainPage' // 目标url
          //   // }, router.RouterMode.Standard, (err) => {
          //   //   if (err) {
          //   //     console.error(`Invoke pushUrl failed, code is ${err.code}, message is ${err.message}`);
          //   //     return;
          //   //   }
          //   //   console.info('Invoke pushUrl succeeded.');
          //   // });
          // })

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