import router from '@ohos.router';
import axios from "@ohos/axios";

@Entry
@Component
struct Index {
  @State username: string = ''
  @State password: string = ''

  build() {
    Flex({direction:FlexDirection.Column,alignItems:ItemAlign.Center,justifyContent:FlexAlign.SpaceAround}){

      Text('农业灌溉登入端')
        .fontSize(24)
        .fontColor(0xCC6CE7)
        .fontWeight(FontWeight.Bold)

      Column({space:10}){
      TextInput({placeholder:'用户名：'})
        .onChange((value) =>{
          this.username = value
        })
      TextInput({placeholder:'密码：'})
        .type(InputType.Password)
        .onChange((value) =>{
          this.password = value
        })
      Button('登陆')
        .width('95%') .margin({top:10})
        .onClick(() =>{
          router.pushUrl({
            url:'pages/LoadingPage',
            //还需要式北来写全局变量更新：username,password
            params:{
              'userName':this.username,
              'userPassword':this.password
            }
          })
          // axios({
          //   method:"get",
          //   url:'http://47.108.250.206:8080/login',
          //   params:{
          //     userName:this.username,
          //     userPassword:this.password
          //   }
          // }).then(res=>{
          //   if(res.data){
          //     router.pushUrl({
          //       url:'pages/LoadingPage',
          //       //还需要式北来写全局变量更新：username,password
          //     })
          //   }else{
          //     //还需要式北来写没成功登陆的界面
          //   }
          // })
        })
      Button('注册') .width('95%')
        .backgroundColor(Color.Gray)
        .margin({top:10})
    }
    .width('90%')
    }
    .width('100%')
    .height('100%')
  }

  //页面切换
  pageTransition(){
    PageTransitionEnter({ duration: 600 })
      .opacity(0)
    PageTransitionExit({ duration: 600 })
      .opacity(0)
  }
}