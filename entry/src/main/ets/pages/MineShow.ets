import UserInfoBean from '../Common/Bean/UserInfoBean'
import router from '@ohos.router';

@Entry
@Component
struct UseInfoShow{
  @State user: UserInfoBean = new UserInfoBean("老张","without",[]);

  @Builder ElementShow(name: String, detail: any) {
    Row() {
      Text(`${name}`)
        .fontSize(22)
        .fontWeight(FontWeight.Bold)
      Text(`${detail}`)
        .fontSize(20)

    }
    .width('95%')
    .justifyContent(FlexAlign.SpaceBetween)

    Divider()
      .width('95%')
  }

  build(){
    Column(){
      this.ElementShow("用户名",this.user.Username)
      this.ElementShow("头像",this.user.Username)
      this.ElementShow("管理的农田",this.user.Username)
      Button("返回")
        .onClick(()=>{
          router.back({
            url: 'pages/MainPage'
          })
        })
    }
  }
}