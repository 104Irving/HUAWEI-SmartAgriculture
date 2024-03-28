import router from '@ohos.router'
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
            url : 'pages/LoadingPage'
          })
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

  pageTransition(){
    PageTransitionEnter({ duration: 600 })
      .opacity(0)
    PageTransitionExit({ duration: 600 })
      .opacity(0)
  }
}