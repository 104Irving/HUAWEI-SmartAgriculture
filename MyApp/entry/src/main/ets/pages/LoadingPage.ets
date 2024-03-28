import router from '@ohos.router'

@Entry
@Component
struct LoadingPage{
  @State message: string = '少女祈祷中......'
  build(){
    Row(){
      Column(){
        Text(this.message)
          .fontSize(30)
          .fontWeight(FontWeight.Bold)
          .fontColor(Color.Black)

        Button('登陆')
          .width('95%') .margin({top:10})
          .onClick(() =>{
            router.pushUrl({
              url: 'pages/MainPage' // 目标url
            }, router.RouterMode.Standard, (err) => {
              if (err) {
                console.error(`Invoke pushUrl failed, code is ${err.code}, message is ${err.message}`);
                return;
              }
              console.info('Invoke pushUrl succeeded.');
            });
          })

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